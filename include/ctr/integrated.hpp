#pragma once
#include "ctr/kernel.hpp"
#include "ctr/effects.hpp"

// Synthetic integration fixture only; not official game semantics.
namespace ctr::integrated {
struct State {
    kernel::State board;
    effects::State resources;
    bool operator==(const State&) const = default;
};
struct Observation {
    kernel::Observation board;
    effects::State resources; // both balances are public in this fixture
    bool operator==(const Observation&) const = default;
};
struct Result {
    State state;
    std::vector<effects::Record> trace;
    bool operator==(const Result&) const = default;
};
inline bool valid(State const& s) {
    return kernel::valid(s.board) && effects::valid(s.resources);
}
inline Observation observe(State const& s, kernel::Player viewer) {
    if (!valid(s)) throw std::invalid_argument("integrated state");
    return {kernel::observe(s.board, viewer), s.resources};
}
// Cost is derived from the PRE-action public zones, never from labels.
inline unsigned cost(kernel::Observation const& o, kernel::Player actor) {
    unsigned count = 0;
    for (auto const& v : o.visible)
        if (v.owner == actor && v.object.zone == kernel::Zone::public_area) ++count;
    if (!kernel::valid(actor) || count > 2) throw std::invalid_argument("modifier input");
    return 3 - count;
}
inline effects::Program program() {
    effects::Program p;
    for (std::uint8_t actor = 0; actor < 2; ++actor) {
        const effects::Event high{effects::Kind::debit, actor, 3};
        const effects::Event low{effects::Kind::debit, actor, 2};
        p.replacements.push_back({unsigned(actor)+1, high, low});
        p.triggers.push_back({unsigned(actor)+1, low,
            {effects::Kind::credit, std::uint8_t(1-actor), 1}});
    }
    return p;
}
inline effects::Result payment(Observation const& o, kernel::Action a) {
    if (a.kind == kernel::ActionKind::pass) return {o.resources, {}};
    const std::array root{effects::Event{effects::Kind::debit, std::uint8_t(a.actor.value),
        std::uint8_t(cost(o.board, a.actor))}};
    return effects::resolve(o.resources, root, program());
}
// Only trusted projections from observe() are accepted as policy inputs.
inline std::vector<kernel::Action> actions(Observation const& o) {
    std::vector<kernel::Action> out;
    if (!effects::valid(o.resources)) throw std::invalid_argument("observation resources");
    for (auto a : kernel::actions(o.board)) {
        try { (void)payment(o, a); } catch (const std::invalid_argument&) { continue; }
        out.push_back(a);
    }
    return out;
}
inline Result apply(State const& s, kernel::Action a) {
    if (!valid(s) || !kernel::legal(s.board, a)) throw std::invalid_argument("integrated action");
    auto pay = payment(observe(s, a.actor), a);
    auto next = State{kernel::apply(s.board, a), pay.state};
    if (!valid(next)) throw std::invalid_argument("integrated invariant");
    return {next, std::move(pay.trace)};
}
using ActionBytes = std::array<std::uint8_t, 4>;
inline ActionBytes encode(kernel::Action a) {
    if (!kernel::valid(a.actor) ||
        !((a.kind == kernel::ActionKind::pass && a.target.value == 0) ||
          (a.kind == kernel::ActionKind::reveal && a.target.value < 4 && kernel::owner(a.target) == a.actor)))
        throw std::invalid_argument("action encoding");
    return {1, std::uint8_t(a.actor.value), std::uint8_t(a.kind), std::uint8_t(a.target.value)};
}
inline kernel::Action decode(std::span<const std::uint8_t> b) {
    if (b.size() != 4 || b[0] != 1) throw std::invalid_argument("action version/size");
    kernel::Action a{kernel::Player{b[1]}, static_cast<kernel::ActionKind>(b[2]), kernel::Entity{b[3]}};
    (void)encode(a);
    return a;
}
using StateBytes = std::array<std::uint8_t, 26>;
inline StateBytes encode(State const& s) {
    if (!valid(s)) throw std::invalid_argument("state encoding");
    StateBytes b{1, s.board.turn, std::uint8_t(s.board.priority.value), std::uint8_t(s.board.passed),
        std::uint8_t(s.resources.balance[0]), std::uint8_t(s.resources.balance[1])};
    unsigned i = 6;
    for (auto const& o : s.board.objects) {
        b[i++] = std::uint8_t(o.zone);
        for (unsigned j = 0; j < 4; ++j) b[i++] = std::uint8_t(o.label >> (8*j));
    }
    return b;
}
inline State decode_state(std::span<const std::uint8_t> b) {
    if (b.size() != 26 || b[0] != 1 || b[3] > 1) throw std::invalid_argument("state version/size");
    State s;
    s.board.turn = b[1]; s.board.priority = kernel::Player{b[2]}; s.board.passed = b[3] != 0;
    s.resources.balance = {b[4], b[5]};
    unsigned i = 6;
    for (auto& o : s.board.objects) {
        o.zone = static_cast<kernel::Zone>(b[i++]);
        for (unsigned j = 0; j < 4; ++j) o.label |= std::uint32_t(b[i++]) << (8*j);
    }
    if (!valid(s)) throw std::invalid_argument("state encoding");
    return s;
}
// Version-1 replay re-executes the immutable synthetic rules; no random input.
inline State replay(StateBytes initial, std::span<const ActionBytes> log) {
    if (log.size() > 32) throw std::invalid_argument("replay limit");
    auto s = decode_state(initial);
    for (auto const& b : log) s = apply(s, decode(b)).state;
    return s;
}
} // namespace ctr::integrated
