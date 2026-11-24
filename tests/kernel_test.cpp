#include "ctr/kernel.hpp"
#include <algorithm>
#include <iostream>
using namespace ctr::kernel;
void check(bool ok) { if (!ok) throw std::runtime_error("kernel check failed"); }
template<class F> void rejects(F f) {
    try { f(); } catch (const std::invalid_argument&) { return; }
    throw std::runtime_error("expected rejection");
}
int main() {
    unsigned states = 0, candidates = 0, projections = 0;
    for (unsigned mask = 0; mask < 16; ++mask)
    for (unsigned turn = 0; turn <= 3; ++turn)
    for (unsigned priority = 0; priority < 2; ++priority)
    for (bool passed : {false, true}) {
        State s{};
        s.turn = std::uint8_t(turn); s.priority = Player{priority}; s.passed = passed;
        for (unsigned i = 0; i < 4; ++i) s.objects[i] = {mask & (1u << i) ? Zone::public_area : Zone::private_area, 100 + i};
        if (turn == 3 && (priority != 0 || passed)) {
            check(!valid(s)); rejects([&] { (void)observe(s, Player{0}); }); continue;
        }
        check(valid(s)); ++states;
        for (unsigned p = 0; p < 2; ++p) {
            const auto obs = observe(s, Player{p});
            const auto offered = actions(obs);
            unsigned expected_count = 0;
            auto altered = s;
            for (unsigned i = 0; i < 4; ++i)
                if (i / 2 != p && !(mask & (1u << i))) altered.objects[i].label += 999;
            check(obs == observe(altered, Player{p}));
            check(offered == actions(observe(altered, Player{p}))); ++projections;
            unsigned private_count[2]{};
            unsigned visible_count = 0;
            for (unsigned i = 0; i < 4; ++i) {
                const bool public_object = (mask & (1u << i)) != 0;
                if (!public_object) ++private_count[i / 2];
                const bool visible = public_object || i / 2 == p;
                if (visible) ++visible_count;
                check(std::count_if(obs.visible.begin(), obs.visible.end(), [&](auto const& v) {
                    return v.id.value == i && v.owner.value == i / 2 && v.object == s.objects[i];
                }) == (visible ? 1 : 0));
            }
            check(obs.visible.size() == visible_count && obs.private_counts[0] == private_count[0] && obs.private_counts[1] == private_count[1]);
            for (unsigned k = 0; k < 3; ++k) for (unsigned target = 0; target < 5; ++target) {
                Action a{Player{p}, static_cast<ActionKind>(k), Entity{target}};
                const bool allowed = turn < 3 && p == priority &&
                    ((k == 0 && target == 0) || (k == 1 && target < 4 && target / 2 == p && !(mask & (1u << target))));
                ++candidates;
                check(legal(s, a) == allowed);
                check(std::count(offered.begin(), offered.end(), a) == (allowed ? 1 : 0));
                if (!allowed) { rejects([&] { (void)apply(s, a); }); continue; }
                ++expected_count;
                auto expected = s;
                if (k == 1) { expected.objects[target].zone = Zone::public_area; expected.passed = false; expected.priority = Player{1-p}; }
                else if (!passed) { expected.passed = true; expected.priority = Player{1-p}; }
                else { expected.turn = std::uint8_t(turn+1); expected.passed = false; expected.priority = Player{turn == 2 ? 0u : (turn+1)%2}; }
                const auto result = apply(s, a);
                check(result == expected && valid(result));
                check(s.objects[0].label == 100 && s.turn == turn && s.priority.value == priority && s.passed == passed);
            }
            check(offered.size() == expected_count);
        }
    }
    State s{};
    rejects([&] { (void)observe(s, Player{2}); });
    rejects([&] { (void)apply(s, {Player{2}, ActionKind::pass, Entity{0}}); });
    s.objects[0].zone = static_cast<Zone>(255);
    check(!valid(s)); rejects([&] { (void)observe(s, Player{0}); });
    check(states == 208 && candidates == 6240 && projections == 416);
    std::cout << "kernel-v1:" << states << " states:" << candidates << " candidates:" << projections << " projections\n";
}
