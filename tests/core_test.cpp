#include "ctr/core.hpp"
#include <iostream>
#include <limits>
#include <type_traits>
#include <vector>

using namespace ctr;
using namespace ctr::fixture;
void check(bool ok) { if (!ok) throw std::runtime_error("check failed"); }
template<class F> void rejects(F f) {
    try { f(); } catch (const std::invalid_argument&) { return; }
    throw std::runtime_error("expected rejection");
}
struct Script {
    std::vector<std::uint64_t> values;
    std::size_t pos{};
    std::uint64_t next() { return values.at(pos++); }
};
struct PlayerTag;
struct ObjectTag;
static_assert(!std::is_convertible_v<Id<PlayerTag>, Id<ObjectTag>>);
static_assert(!std::is_convertible_v<std::uint32_t, Id<PlayerTag>>);

int main() {
    Random game(42, Stream::gameplay, 7), duplicate(42, Stream::gameplay, 7);
    Random agent(42, Stream::agent, 7), opt(42, Stream::optimizer, 7);
    Random other(42, Stream::gameplay, 8);
    const auto first = game.next();
    check(first == 871378669735641285ULL && first == duplicate.next());
    check(first != agent.next() && first != opt.next() && first != other.next());
    std::cout << "rng-v1:" << first << '\n';
    for (int i = 0; i < 1000; ++i) {
        (void)agent.next(); (void)opt.next();
        check(game.next() == duplicate.next());
    }
    rejects([] { Random r(0, static_cast<Stream>(0), 0); (void)r; });
    Script reject_then_accept{{0, 5, 6}};
    check(bounded(reject_then_accept, 10) == 6 && reject_then_accept.pos == 3);
    Script edge{{0, std::numeric_limits<std::uint64_t>::max()}};
    check(bounded(edge, 1) == 0);
    check(bounded(edge, std::numeric_limits<std::uint64_t>::max()) == 0);
    rejects([&] { (void)bounded(edge, 0); });
    check(encode(State{42, false}) == Bytes{1, 42, 0});
    check(encode(Event{Kind::outcome, 6}) == Bytes{1, 3, 6});
    const std::array<Bytes, 3> trace{{{1, 1, 0}, {1, 2, 0}, {1, 3, 6}}};
    check(replay({1, 0, 0}, trace) == State{7, false});
    check(replay({1, 0, 0}, std::span(trace).first(2)) == State{1, true});
    rejects([&] { (void)replay({1, 94, 0}, trace); });
    rejects([] { (void)decode_state(Bytes{2, 0, 0}); });
    rejects([] { (void)decode_event(Bytes{2, 1, 0}); });
    rejects([] { (void)decode_state(std::array<std::uint8_t, 2>{1, 0}); });
    rejects([] { (void)decode_event(std::array<std::uint8_t, 4>{1, 1, 0, 0}); });
    // Exhaustive wire-domain checks, with independent validity predicates.
    for (unsigned a = 0; a < 256; ++a) for (unsigned b = 0; b < 256; ++b) {
        Bytes bytes{1, std::uint8_t(a), std::uint8_t(b)};
        if (a <= 100 && (b == 0 || (b == 1 && a <= 94)))
            check(encode(decode_state(bytes)) == bytes);
        else rejects([&] { (void)decode_state(bytes); });
        if (((a == 1 || a == 2) && b == 0) || (a == 3 && b >= 1 && b <= 6))
            check(encode(decode_event(bytes)) == bytes);
        else rejects([&] { (void)decode_event(bytes); });
    }
    const std::array<Event, 8> all{{{Kind::increment, 0}, {Kind::request, 0},
        outcomes[0], outcomes[1], outcomes[2], outcomes[3], outcomes[4], outcomes[5]}};
    for (unsigned v = 0; v <= 100; ++v) for (bool p : {false, true}) {
        if (p && v > 94) continue;
        State s{std::uint8_t(v), p};
        for (const auto e : all) {
            const bool allowed = p ? e.kind == Kind::outcome :
                (e.kind == Kind::increment ? v < 100 : e.kind == Kind::request && v <= 94);
            check(legal(s, e) == allowed);
            if (allowed) {
                const unsigned expected = v + (e.kind == Kind::increment ? 1 : e.payload);
                check(apply(s, e) == State{std::uint8_t(expected), e.kind == Kind::request});
            } else rejects([&] { (void)apply(s, e); });
        }
    }
    std::uint64_t fingerprint = 0;
    for (std::uint64_t run = 0; run < 1000; ++run) {
        Random rng(123456, Stream::gameplay, run), policy(123456, Stream::agent, run);
        State s{};
        std::vector<Bytes> events;
        while (s.value < 100) {
            Event e{Kind::increment, 0};
            if (s.pending) e = sample(s, rng);
            else if (s.value <= 94 && bounded(policy, 2) == 1) e = {Kind::request, 0};
            s = apply(s, e);
            check(valid(s));
            events.push_back(encode(e));
            for (const auto byte : events.back()) fingerprint = fingerprint * 257 + byte;
            for (const auto byte : encode(s)) fingerprint = fingerprint * 257 + byte;
            check(replay({1, 0, 0}, events) == s);
        }
        check(!s.pending);
    }
    rejects([&] { (void)sample(State{}, game); });
    check(game.next() == duplicate.next());
    rejects([] { (void)apply(State{101, false}, Event{Kind::increment, 0}); });
    rejects([] { (void)apply(State{}, Event{static_cast<Kind>(255), 0}); });
    check(fingerprint == 4864969216242844801ULL);
    std::cout << "core-v1:1000 traces:" << fingerprint << '\n';
}
