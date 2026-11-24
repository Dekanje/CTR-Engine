#include "ctr/integrated.hpp"
#include <iostream>
#include <string>
namespace m = ctr::modifiers;
namespace e = ctr::effects;
namespace i = ctr::integrated;
namespace k = ctr::kernel;
void check(bool ok) { if (!ok) throw std::runtime_error("modifier check failed"); }
template<class E, class F> void rejects(F f) {
    try { f(); } catch (const E&) { return; }
    throw std::runtime_error("expected rejection");
}
// Must not be mistaken for resource-based illegality.
template<class F> void config_error(F f) {
    try { f(); } catch (const e::ResourceViolation&) { throw std::runtime_error("misclassified resource error"); }
    catch (const i::IllegalAction&) { throw std::runtime_error("misclassified action error"); }
    catch (const std::invalid_argument&) { return; }
    throw std::runtime_error("expected configuration error");
}
int main() {
    using O = m::Operation;
    std::array rules{m::Rule{1,1,1,O::add,2},m::Rule{2,0,2,O::set,4},
        m::Rule{3,1,4,O::multiply,2},m::Rule{4,2,8,O::add,-1}};
    unsigned cases = 0;
    do {
        for (unsigned mask=0; mask<16; ++mask) for (unsigned base=1; base<=20; ++base) {
            int want = mask&2 ? 4 : int(base);
            if (mask&1) want+=2;
            if (mask&4) want*=2;
            if (mask&8) --want;
            check(m::evaluate(base,mask,rules)==unsigned(want)); ++cases;
        }
    } while (std::next_permutation(rules.begin(),rules.end(),[](auto a,auto b){return a.id<b.id;}));
    const std::array multi{m::Rule{1,0,3,O::add,2}};
    check(m::evaluate(5,1,multi)==5 && m::evaluate(5,3,multi)==7 && m::evaluate(5,2,multi)==5);
    check(m::evaluate(100,0,{})==100 && m::evaluate(0,0,{})==0);
    config_error([]{ (void)m::evaluate(101,0,{}); });
    config_error([]{ (void)m::evaluate(0,16,{}); });
    config_error([]{ (void)m::evaluate(0,0,std::array<m::Rule,65>{}); });
    config_error([]{ (void)m::evaluate(1,0,std::array{m::Rule{1,0,1,static_cast<O>(255),0}}); });
    config_error([]{ (void)m::evaluate(1,0,std::array{m::Rule{1,0,1,O::multiply,5}}); });
    config_error([]{ (void)m::evaluate(1,0,std::array{m::Rule{0,0,1,O::add,1}}); });
    config_error([]{ (void)m::evaluate(1,0,std::array{m::Rule{1,8,1,O::add,1}}); });
    config_error([]{ (void)m::evaluate(1,0,std::array{m::Rule{1,0,16,O::add,1}}); });
    config_error([]{ (void)m::evaluate(1,0,std::array{m::Rule{1,0,1,O::add,1},m::Rule{1,1,2,O::set,1}}); });
    config_error([]{ (void)m::evaluate(100,0,std::array{m::Rule{1,0,0,O::add,1}}); });
    config_error([]{ (void)m::evaluate(0,0,std::array{m::Rule{1,0,0,O::add,-1}}); });
    // Independent variable-price fixture: active flag reduces root debit 5 to 3;
    // replacement 5->4 and trigger 3->credit produce distinct final balances.
    const std::array discount{m::Rule{1,0,1,O::add,-2}};
    const e::Event debit5{e::Kind::debit,0,5}, debit4{e::Kind::debit,0,4}, debit3{e::Kind::debit,0,3};
    const e::Program prog{1,{{1,debit5,debit4}},{{1,debit3,{e::Kind::credit,1,1}}}};
    const e::State funds{{10,10}};
    for (unsigned mask : {0u,1u,0u}) {
        const std::array root{e::Event{e::Kind::debit,0,std::uint8_t(m::evaluate(5,mask,discount))}};
        const auto result=e::resolve(funds,root,prog);
        check(result.state.balance==(mask?std::array<unsigned,2>{7,11}:std::array<unsigned,2>{6,10}));
        check(result.trace.size()==(mask?2u:1u));
    }
    const std::array root{debit3};
    rejects<e::ResourceViolation>([&]{ (void)e::resolve(e::State{{2,10}},root,prog); });
    rejects<e::ResourceViolation>([&]{ (void)e::resolve(e::State{{10,100}},root,prog); });
    auto bad=prog; bad.version=2;
    config_error([&]{ (void)e::resolve(funds,root,bad); });
    const e::Program loop{1,{{1,debit3,debit3}}, {}};
    config_error([&]{ (void)e::resolve(funds,root,loop); });
    const e::Program cascade{1,{},{{1,debit3,debit3}}};
    config_error([&]{ (void)e::resolve(funds,root,cascade,{1,1,1}); });
    i::State s; s.resources.balance={10,10};
    const k::Action reveal{k::Player{0},k::ActionKind::reveal,k::Entity{0}};
    auto obs=i::observe(s,k::Player{0});
    check(i::actions(obs).size()==3);
    s.resources.balance[0]=1;
    check(i::actions(i::observe(s,k::Player{0})).size()==1);
    rejects<e::ResourceViolation>([&]{ (void)i::apply(s,reveal); });
    rejects<i::IllegalAction>([&]{ (void)i::apply(s,{k::Player{1},k::ActionKind::pass,k::Entity{0}}); });
    s.resources.balance[0]=101;
    config_error([&]{ (void)i::apply(s,reveal); });
    // Malformed trusted projection: duplicate public slot, plus a private candidate.
    obs.board.visible[0].object.zone=k::Zone::public_area;
    obs.board.visible.push_back(obs.board.visible[0]);
    config_error([&]{ (void)i::actions(obs); });
    check(cases==7680);
    std::cout << "modifiers-v1:" << cases << " ordered cases\n";
}
