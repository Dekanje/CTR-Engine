#include "ctr/conflict.hpp"
#include <iostream>
using namespace ctr::conflict;
void check(bool ok) { if (!ok) throw std::runtime_error("conflict check failed"); }
template<class F> void rejects(F f) {
    try { f(); } catch (const std::invalid_argument&) { return; }
    throw std::runtime_error("expected rejection");
}
int main() {
    unsigned cases=0, accepted=0;
    // Exhaustive small health/power domain, all order vectors including illegal targets.
    const std::array<Unit,5> units{{{0,0},{1,1},{1,2},{2,1},{2,2}}};
    for (auto a:units) for (auto b:units) for (auto c:units) for (auto d:units) {
        State s{{a,b,c,d},{std::uint8_t((c.hp==0)+(d.hp==0)),std::uint8_t((a.hp==0)+(b.hp==0))},0};
        for (std::uint8_t round : {std::uint8_t{0},std::uint8_t{3},std::uint8_t{4}}) {
            s.round=round; const auto before=s;
            check(decode_state(encode(s))==s);
            for (unsigned n=0;n<625;++n) {
                unsigned q=n; Orders o{};
                for (auto& t:o) { t=std::uint8_t(q%5); q/=5; }
                bool allowed=round<4 && s.score[0]<2 && s.score[1]<2;
                for (unsigned j=0;j<4;++j) if (o[j]!=4)
                    allowed=allowed && s.units[j].hp!=0 && s.units[o[j]].hp!=0 && (j<2)!=(o[j]<2);
                check(legal(s,o)==allowed); ++cases;
                if (!allowed) continue;
                ++accepted;
                auto want=s; ++want.round;
                for (unsigned target=0;target<4;++target) {
                    int hp=s.units[target].hp;
                    for (unsigned source=0;source<4;++source) if (o[source]==target) hp-=s.units[source].power;
                    if (hp<=0) want.units[target]={}; else want.units[target].hp=std::uint8_t(hp);
                }
                want.score={std::uint8_t((want.units[2].hp==0)+(want.units[3].hp==0)),
                            std::uint8_t((want.units[0].hp==0)+(want.units[1].hp==0))};
                const auto got=resolve_round(s,o); check(got==want && valid(got) && s==before);
                const bool terminal=want.round==4 || want.score[0]==2 || want.score[1]==2;
                const auto expected=!terminal?Outcome::ongoing:want.score[0]==want.score[1]?Outcome::draw:
                    want.score[0]>want.score[1]?Outcome::first:Outcome::second;
                check(outcome(got)==expected);
                check(replay(encode(s),std::array<OrderBytes,1>{encode(o)})==want);
            }
        }
    }
    const State start{{Unit{3,3},Unit{3,3},Unit{3,3},Unit{3,3}},{0,0},0};
    const Orders mutual{2,3,0,1}, focus{2,2,0,0}, wait{4,4,4,4};
    const auto draw=resolve_round(start,mutual); check(outcome(draw)==Outcome::draw && draw.score==std::array<std::uint8_t,2>{2,2});
    const auto focused=resolve_round(start,focus); check(focused.score==std::array<std::uint8_t,2>{1,1} && focused.units[0]==Unit{} && focused.units[2]==Unit{});
    const std::array log{encode(focus),encode(Orders{4,3,4,4})};
    check(outcome(replay(encode(start),log))==Outcome::first);
    check(outcome(resolve_round(start,Orders{4,4,0,1}))==Outcome::second);
    check(outcome(replay(encode(start),std::array{encode(wait),encode(wait),encode(wait),encode(wait)}))==Outcome::draw);
    rejects([&]{ (void)resolve_round(draw,wait); });
    rejects([&]{ (void)resolve_round(start,Orders{0,4,4,4}); });
    rejects([&]{ (void)resolve_round(start,Orders{255,4,4,4}); });
    rejects([&]{ (void)resolve_round(focused,mutual); });
    rejects([&]{ (void)replay(encode(start),std::array{encode(mutual),encode(wait)}); });
    rejects([&]{ (void)replay(encode(start),std::array<OrderBytes,5>{}); });
    auto bad=encode(start); bad[2]=1; rejects([&]{ (void)decode_state(bad); });
    bad=encode(start); bad[4]=0; rejects([&]{ (void)decode_state(bad); });
    bad=encode(start); bad[0]=2; rejects([&]{ (void)decode_state(bad); });
    rejects([]{ (void)decode_orders(OrderBytes{1,5,4,4,4}); });
    rejects([]{ (void)decode_orders(OrderBytes{2,4,4,4,4}); });
    rejects([]{ (void)decode_orders(std::array<std::uint8_t,1>{1}); });
    check(cases==1171875);
    std::cout << "conflict-v1:" << cases << " candidates:" << accepted << " accepted\n";
}
