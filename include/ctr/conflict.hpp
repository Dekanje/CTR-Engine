#pragma once
#include "ctr/core.hpp"

// Standalone synthetic simultaneous-conflict fixture, not game semantics.
namespace ctr::conflict {
struct Unit {
    std::uint8_t hp = 0, power = 0;
    bool operator==(const Unit&) const = default;
};
struct State {
    std::array<Unit, 4> units{};
    std::array<std::uint8_t, 2> score{};
    std::uint8_t round = 0;
    bool operator==(const State&) const = default;
};
constexpr std::uint8_t idle = 4, round_limit = 4;
using Orders = std::array<std::uint8_t, 4>;
enum class Outcome { ongoing, first, second, draw };
inline bool valid(State const& s) {
    if (s.round > round_limit) return false;
    std::array<unsigned, 2> dead{};
    for (unsigned j = 0; j < 4; ++j) {
        const auto u = s.units[j];
        if (u.hp > 3 || u.power > 3 || ((u.hp == 0) != (u.power == 0))) return false;
        if (u.hp == 0) ++dead[j/2];
    }
    return s.score[0] == dead[1] && s.score[1] == dead[0];
}
inline Outcome outcome(State const& s) {
    if (!valid(s)) throw std::invalid_argument("conflict state");
    if (s.round < round_limit && s.score[0] < 2 && s.score[1] < 2) return Outcome::ongoing;
    if (s.score[0] == s.score[1]) return Outcome::draw;
    return s.score[0] > s.score[1] ? Outcome::first : Outcome::second;
}
inline bool legal(State const& s, Orders const& orders) {
    if (!valid(s) || outcome(s) != Outcome::ongoing) return false;
    for (unsigned j = 0; j < 4; ++j) {
        const auto t = orders[j];
        if (t == idle) continue;
        if (t >= 4 || j/2 == t/2 || s.units[j].hp == 0 || s.units[t].hp == 0) return false;
    }
    return true;
}
inline State resolve_round(State const& s, Orders const& orders) {
    if (!legal(s, orders)) throw std::invalid_argument("conflict orders");
    std::array<unsigned, 4> damage{};
    for (unsigned j = 0; j < 4; ++j)
        if (orders[j] != idle) damage[orders[j]] += s.units[j].power;
    auto next = s;
    for (unsigned j = 0; j < 4; ++j) {
        if (damage[j] == 0) continue;
        if (damage[j] >= s.units[j].hp) {
            next.units[j] = {};
            ++next.score[1-j/2];
        } else next.units[j].hp = std::uint8_t(s.units[j].hp - damage[j]);
    }
    ++next.round;
    if (!valid(next)) throw std::logic_error("conflict invariant");
    return next;
}
using StateBytes = std::array<std::uint8_t, 12>;
using OrderBytes = std::array<std::uint8_t, 5>;
inline StateBytes encode(State const& s) {
    if (!valid(s)) throw std::invalid_argument("conflict state");
    StateBytes b{1,s.round,s.score[0],s.score[1]};
    for (unsigned j=0; j<4; ++j) { b[4+2*j]=s.units[j].hp; b[5+2*j]=s.units[j].power; }
    return b;
}
inline State decode_state(std::span<const std::uint8_t> b) {
    if (b.size()!=12 || b[0]!=1) throw std::invalid_argument("conflict state encoding");
    State s; s.round=b[1]; s.score={b[2],b[3]};
    for (unsigned j=0; j<4; ++j) s.units[j]={b[4+2*j],b[5+2*j]};
    if (!valid(s)) throw std::invalid_argument("conflict state");
    return s;
}
inline OrderBytes encode(Orders const& o) {
    for (auto t:o) if (t>idle) throw std::invalid_argument("conflict order encoding");
    return {1,o[0],o[1],o[2],o[3]};
}
inline Orders decode_orders(std::span<const std::uint8_t> b) {
    if (b.size()!=5 || b[0]!=1) throw std::invalid_argument("conflict order encoding");
    Orders o{b[1],b[2],b[3],b[4]}; (void)encode(o); return o;
}
inline State replay(StateBytes initial, std::span<const OrderBytes> log) {
    if (log.size()>round_limit) throw std::invalid_argument("conflict replay limit");
    auto s=decode_state(initial);
    for (auto const& b:log) s=resolve_round(s,decode_orders(b));
    return s;
}
} // namespace ctr::conflict
