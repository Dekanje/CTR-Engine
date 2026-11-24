#pragma once
#include <array>
#include <cstdint>
#include <random>
#include <span>
#include <stdexcept>

namespace ctr {
template<class Tag> struct Id {
    explicit constexpr Id(std::uint32_t v) : value(v) {}
    std::uint32_t value;
    constexpr bool operator==(const Id&) const = default;
};

enum class Stream : std::uint32_t { gameplay = 1, agent = 2, optimizer = 3 };

// Version 1: seed_seq(root low/high, domain, run low/high), mt19937_64.
class Random {
    std::mt19937_64 engine_;
public:
    Random(std::uint64_t root, Stream domain, std::uint64_t run) {
        const auto d = static_cast<std::uint32_t>(domain);
        if (d < 1 || d > 3) throw std::invalid_argument("stream domain");
        std::seed_seq seed{std::uint32_t(root), std::uint32_t(root >> 32), d,
                           std::uint32_t(run), std::uint32_t(run >> 32)};
        engine_.seed(seed);
    }
    std::uint64_t next() { return engine_(); }
};

// Full-width uniform input required; rejection avoids modulo bias.
template<class Source> std::uint64_t bounded(Source& source, std::uint64_t n) {
    if (n == 0) throw std::invalid_argument("zero bound");
    const auto threshold = (std::uint64_t{0} - n) % n;
    for (;;) {
        const std::uint64_t x = source.next();
        if (x >= threshold) return x % n;
    }
}

// Synthetic fixture only. Not a game rule or production state schema.
namespace fixture {
struct State {
    std::uint8_t value{};
    bool pending{};
    bool operator==(const State&) const = default;
};
enum class Kind : std::uint8_t { increment = 1, request = 2, outcome = 3 };
struct Event {
    Kind kind;
    std::uint8_t payload{};
    bool operator==(const Event&) const = default;
};
using Bytes = std::array<std::uint8_t, 3>;
inline bool valid(State s) { return s.value <= 100 && (!s.pending || s.value <= 94); }
inline bool valid(Event e) {
    switch (e.kind) {
        case Kind::increment: case Kind::request: return e.payload == 0;
        case Kind::outcome: return e.payload >= 1 && e.payload <= 6;
    }
    return false;
}
inline Bytes encode(State s) {
    if (!valid(s)) throw std::invalid_argument("state");
    return {1, s.value, std::uint8_t(s.pending)};
}
inline Bytes encode(Event e) {
    if (!valid(e)) throw std::invalid_argument("event");
    return {1, static_cast<std::uint8_t>(e.kind), e.payload};
}
inline State decode_state(std::span<const std::uint8_t> b) {
    if (b.size() != 3 || b[0] != 1 || b[2] > 1) throw std::invalid_argument("state encoding");
    State s{b[1], b[2] == 1};
    if (!valid(s)) throw std::invalid_argument("state");
    return s;
}
inline Event decode_event(std::span<const std::uint8_t> b) {
    if (b.size() != 3 || b[0] != 1) throw std::invalid_argument("event encoding");
    Event e{static_cast<Kind>(b[1]), b[2]};
    if (!valid(e)) throw std::invalid_argument("event");
    return e;
}
inline bool legal(State s, Event e) {
    if (!valid(s) || !valid(e)) return false;
    if (s.pending) return e.kind == Kind::outcome;
    return (e.kind == Kind::increment && s.value < 100) ||
           (e.kind == Kind::request && s.value <= 94);
}
inline State apply(State s, Event e) {
    if (!legal(s, e)) throw std::invalid_argument("illegal transition");
    if (e.kind == Kind::request) s.pending = true;
    else {
        s.value = std::uint8_t(s.value + (e.kind == Kind::increment ? 1 : e.payload));
        s.pending = false;
    }
    return s;
}
inline constexpr std::array<Event, 6> outcomes{{
    {Kind::outcome, 1}, {Kind::outcome, 2}, {Kind::outcome, 3},
    {Kind::outcome, 4}, {Kind::outcome, 5}, {Kind::outcome, 6}}};
inline Event sample(State s, Random& rng) {
    if (!valid(s) || !s.pending) throw std::invalid_argument("no pending chance");
    return outcomes[bounded(rng, outcomes.size())];
}
// Replay consumes explicit events, never an RNG. Prefixes may end pending.
inline State replay(Bytes initial, std::span<const Bytes> events) {
    auto s = decode_state(initial);
    for (const auto& b : events) s = apply(s, decode_event(b));
    return s;
}
} // namespace fixture
} // namespace ctr
