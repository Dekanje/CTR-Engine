#include "ctr/integrated.hpp"
#include <iostream>
using namespace ctr;
namespace k = ctr::kernel;
namespace i = ctr::integrated;
void check(bool ok) { if (!ok) throw std::runtime_error("integration check failed"); }
template<class F> void rejects(F f) {
    try { f(); } catch (const std::invalid_argument&) { return; }
    throw std::runtime_error("expected rejection");
}
int main() {
    unsigned cases = 0, views = 0;
    for (unsigned mask = 0; mask < 16; ++mask)
    for (unsigned p = 0; p < 2; ++p)
    for (unsigned own : {0u,1u,2u,3u,99u,100u})
    for (unsigned other : {0u,1u,99u,100u}) {
        i::State s;
        s.board.priority = k::Player{p}; s.resources.balance[p] = own; s.resources.balance[1-p] = other;
        for (unsigned j = 0; j < 4; ++j) s.board.objects[j] = {
            mask & (1u<<j) ? k::Zone::public_area : k::Zone::private_area, 0x12345678u+j};
        const auto before = s;
        check(i::decode_state(i::encode(s)) == s);
        for (unsigned v = 0; v < 2; ++v) {
            const auto obs = i::observe(s,k::Player{v});
            auto altered = s;
            for (unsigned j = 0; j < 4; ++j) if (j/2 != v && !(mask & (1u<<j))) altered.board.objects[j].label ^= 0xffffffffu;
            check(obs == i::observe(altered,k::Player{v}));
            check(i::actions(obs) == i::actions(i::observe(altered,k::Player{v}))); ++views;
        }
        const auto offered = i::actions(i::observe(s,k::Player{p}));
        const unsigned visible = ((mask>>(2*p)) & 1u) + ((mask>>(2*p+1)) & 1u);
        check(i::cost(i::observe(s,k::Player{p}).board,k::Player{p}) == 3-visible);
        for (unsigned j = 0; j < 4; ++j) {
            const k::Action a{k::Player{p},k::ActionKind::reveal,k::Entity{j}};
            const bool allowed = j/2 == p && !(mask & (1u<<j)) && own >= 2 && other < 100;
            check(std::count(offered.begin(),offered.end(),a) == (allowed ? 1 : 0));
            if (allowed) {
                const auto result = i::apply(s,a);
                auto want = s; want.board.objects[j].zone = k::Zone::public_area;
                want.board.priority = k::Player{1-p}; want.resources.balance[p] -= 2; ++want.resources.balance[1-p];
                check(result.state == want && result.trace.size() == 2);
                check(result.trace[0].replacements.size() == (visible == 0 ? 1u : 0u));
                check(i::replay(i::encode(s),std::array<i::ActionBytes,1>{i::encode(a)}) == want);
            } else rejects([&]{ (void)i::apply(s,a); });
            check(s == before); ++cases;
        }
        const k::Action pass{k::Player{p},k::ActionKind::pass,k::Entity{0}};
        check(std::count(offered.begin(),offered.end(),pass) == 1);
        const auto result = i::apply(s,pass);
        check(result.state.resources == s.resources && result.trace.empty());
    }
    // Exact multi-action trace and terminal replay, including two different modifiers.
    i::State s; s.resources.balance = {10,10};
    s.board.objects[0].label = 0x12345678;
    check(i::encode(s)[7] == 0x78 && i::encode(s)[10] == 0x12);
    const auto initial = i::encode(s);
    const std::array log{i::ActionBytes{1,0,1,0},i::ActionBytes{1,1,0,0},i::ActionBytes{1,0,1,1},
        i::ActionBytes{1,1,0,0},i::ActionBytes{1,0,0,0},i::ActionBytes{1,1,0,0},
        i::ActionBytes{1,0,0,0},i::ActionBytes{1,0,0,0},i::ActionBytes{1,1,0,0}};
    const auto final = i::replay(initial,log);
    check(final.board.turn == 3 && final.resources.balance == std::array<unsigned,2>{6,12});
    check(i::actions(i::observe(final,k::Player{0})).empty());
    for (unsigned n = 0; n <= log.size(); ++n) {
        const auto prefix = i::replay(initial,std::span(log).first(n));
        check(i::decode_state(i::encode(prefix)) == prefix);
    }
    rejects([&]{ (void)i::replay(i::encode(final),std::array<i::ActionBytes,1>{log[1]}); });
    rejects([&]{ (void)i::replay(initial,std::array{log[0],log[0]}); });
    rejects([]{ (void)i::decode(i::ActionBytes{2,0,0,0}); });
    rejects([]{ (void)i::decode(i::ActionBytes{1,0,1,3}); });
    rejects([]{ (void)i::decode(i::ActionBytes{1,2,0,0}); });
    rejects([]{ (void)i::decode(i::ActionBytes{1,0,255,0}); });
    rejects([]{ (void)i::decode(std::array<std::uint8_t,3>{1,0,0}); });
    auto bad = initial; bad[3] = 2; rejects([&]{ (void)i::decode_state(bad); });
    bad = initial; bad[6] = 255; rejects([&]{ (void)i::decode_state(bad); });
    bad = initial; bad[4] = 101; rejects([&]{ (void)i::decode_state(bad); });
    bad = initial; bad[0] = 2; rejects([&]{ (void)i::decode_state(bad); });
    rejects([&]{ (void)i::replay(initial,std::array<i::ActionBytes,33>{}); });
    check(cases == 3072 && views == 1536);
    std::cout << "integrated-v1:" << cases << " candidates:" << views << " projections\n";
}
