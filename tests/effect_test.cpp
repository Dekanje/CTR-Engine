#include "ctr/effects.hpp"
#include <iostream>
using namespace ctr::effects;
void check(bool ok) { if (!ok) throw std::runtime_error("effect check failed"); }
template<class F> void rejects(F f, const char* reason) {
    try { f(); } catch (const std::invalid_argument& e) {
        check(std::string(e.what()) == reason); return;
    }
    throw std::runtime_error("expected rejection");
}
constexpr Event credit(unsigned n, unsigned p = 0) { return {Kind::credit, std::uint8_t(p), std::uint8_t(n)}; }
constexpr Event debit(unsigned n, unsigned p = 0) { return {Kind::debit, std::uint8_t(p), std::uint8_t(n)}; }
int main() {
    unsigned cases = 0;
    for (unsigned b = 0; b <= 100; ++b) for (unsigned n = 1; n <= 100; ++n)
    for (unsigned p = 0; p < 2; ++p) for (bool add : {false, true}) {
        State s{{b,b}}; auto before = s;
        const std::array input{add ? credit(n,p) : debit(n,p)};
        const int expected = int(b) + (add ? int(n) : -int(n));
        if (expected < 0 || expected > 100)
            rejects([&]{ (void)resolve(s,input,{}); }, add ? "overflow" : "underflow");
        else {
            auto result = resolve(s,input,{}); auto want = s; want.balance[p] = unsigned(expected);
            check(result == Result{want, {{input[0], {}, input[0], {}}}});
        }
        check(s == before); ++cases;
    }
    // Exact trace oracle: rewrite by lowest ID, restart, then FIFO triggers.
    const State initial{{5,5}};
    const std::array roots{credit(1), debit(2,1), credit(9)};
    Program prog{1, {{8,credit(1),credit(8)}, {2,credit(1),credit(3)},
                     {4,credit(3),credit(4)}, {9,credit(9),std::nullopt}},
                    {{12,credit(4),debit(1)}, {3,credit(4),credit(2,1)},
                     {6,credit(2,1),credit(1,1)}, {7,credit(1),credit(99)},
                     {8,credit(9),credit(99)}}};
    const Result want{{{8,6}}, {{credit(1),{2,4},credit(4),{3,12}},
        {debit(2,1),{},debit(2,1),{}}, {credit(9),{9},std::nullopt,{}},
        {credit(2,1),{},credit(2,1),{6}}, {debit(1),{},debit(1),{}},
        {credit(1,1),{},credit(1,1),{}}}};
    unsigned permutations = 0;
    auto by_id = [](auto const& a, auto const& b){ return a.id < b.id; };
    std::sort(prog.replacements.begin(),prog.replacements.end(),by_id);
    do {
        std::sort(prog.triggers.begin(),prog.triggers.end(),by_id);
        do { check(resolve(initial,roots,prog) == want); ++permutations; }
        while (std::next_permutation(prog.triggers.begin(),prog.triggers.end(),by_id));
    } while (std::next_permutation(prog.replacements.begin(),prog.replacements.end(),by_id));
    const std::array one{credit(1)};
    const Program cycle{1,{{1,credit(1),credit(2)},{2,credit(2),credit(1)}},{}};
    rejects([&]{ (void)resolve(initial,one,cycle); },"replacement cycle");
    const Program self{1,{{1,credit(1),credit(1)}},{}};
    rejects([&]{ (void)resolve(initial,one,self); },"replacement cycle");
    const Program chain{1,{{1,credit(1),credit(2)},{2,credit(2),credit(3)}},{}};
    rejects([&]{ (void)resolve(initial,one,chain,{4,1,4}); },"rewrite budget");
    check(resolve(initial,one,chain,{1,2,1}).state.balance[0] == 8);
    const Program loop{1,{},{{1,credit(1),debit(1)},{2,debit(1),credit(1)}}};
    rejects([&]{ (void)resolve(initial,one,loop,{8,2,2}); },"event budget");
    const Program fan{1,{},{{1,credit(1),credit(2)},{2,credit(1),credit(3)}}};
    rejects([&]{ (void)resolve(initial,one,fan,{8,2,1}); },"pending budget");
    check(resolve(initial,one,fan,{3,1,2}).state.balance[0] == 11);
    const Program late{1,{},{{1,credit(1),debit(99)}}};
    rejects([&]{ (void)resolve(initial,one,late); },"underflow");
    check(initial == State{{5,5}});
    rejects([&]{ (void)resolve(initial,one,{2,{},{}}); },"state or version");
    rejects([&]{ (void)resolve(State{{101,0}},one,{}); },"state or version");
    rejects([&]{ (void)resolve(initial,one,{}, {0,1,1}); },"limits");
    rejects([&]{ (void)resolve(initial,roots,{}, {2,1,3}); },"input size");
    rejects([&]{ (void)resolve(initial,one,{1,{{1,credit(1),credit(2)},{1,credit(2),credit(3)}},{}}); },"rule id");
    rejects([&]{ (void)resolve(initial,one,{1,{},{{0,credit(1),credit(2)}}}); },"rule id");
    rejects([&]{ (void)resolve(initial,one,{1,{{1,credit(7),credit(0)}},{}}); },"replacement event");
    rejects([&]{ (void)resolve(initial,one,{1,{},{{1,credit(7),credit(1,2)}}}); },"trigger event");
    const std::array invalid{Event{static_cast<Kind>(255),0,1}};
    rejects([&]{ (void)resolve(initial,invalid,{}); },"input event");
    check(resolve(initial,{},{}).state == initial);
    check(cases == 40400 && permutations == 2880);
    std::cout << "effects-v1:" << cases << " balance cases:" << permutations << " permutations\n";
}
