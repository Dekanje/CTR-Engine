#pragma once
#include "ctr/core.hpp"
#include <vector>

// Original synthetic contract fixture. No Riftbound semantics.
namespace ctr::kernel {
struct PlayerTag;
struct EntityTag;
using Player = Id<PlayerTag>;
using Entity = Id<EntityTag>;
enum class Zone : std::uint8_t { private_area, public_area };
enum class ActionKind : std::uint8_t { pass, reveal };
struct Object {
    Zone zone = Zone::private_area;
    std::uint32_t label = 0;
    bool operator==(const Object&) const = default;
};
struct State {
    std::array<Object, 4> objects{}; // two fixed slots per owner
    std::uint8_t turn = 0;
    Player priority{0};
    bool passed = false;
    bool operator==(const State&) const = default;
};
struct Action {
    Player actor;
    ActionKind kind;
    Entity target{0}; // pass requires zero
    bool operator==(const Action&) const = default;
};
struct VisibleObject {
    Entity id;
    Player owner;
    Object object;
    bool operator==(const VisibleObject&) const = default;
};
struct Observation {
    Player viewer;
    std::uint8_t turn;
    Player priority;
    bool passed;
    std::array<unsigned, 2> private_counts{};
    std::vector<VisibleObject> visible;
    bool operator==(const Observation&) const = default;
};
inline constexpr unsigned turn_limit = 3;
inline bool valid(Player p) { return p.value < 2; }
inline bool valid(State const& s) {
    if (!valid(s.priority) || s.turn > turn_limit) return false;
    if (s.turn == turn_limit && (s.priority.value != 0 || s.passed)) return false;
    for (auto const& o : s.objects)
        if (o.zone != Zone::private_area && o.zone != Zone::public_area) return false;
    return true;
}
inline Player owner(Entity id) { return Player{id.value / 2}; }
inline bool legal(State const& s, Action a) {
    if (!valid(s) || s.turn == turn_limit || !valid(a.actor) || a.actor != s.priority) return false;
    switch (a.kind) {
        case ActionKind::pass: return a.target.value == 0;
        case ActionKind::reveal:
            return a.target.value < s.objects.size() && owner(a.target) == a.actor &&
                   s.objects[a.target.value].zone == Zone::private_area;
    }
    return false;
}
inline Observation observe(State const& s, Player viewer) {
    if (!valid(s) || !valid(viewer)) throw std::invalid_argument("observation input");
    Observation out{viewer, s.turn, s.priority, s.passed, {}, {}};
    for (std::uint32_t i = 0; i < s.objects.size(); ++i) {
        const Entity id{i};
        const auto p = owner(id);
        const auto& o = s.objects[i];
        if (o.zone == Zone::private_area) ++out.private_counts[p.value];
        if (p == viewer || o.zone == Zone::public_area) out.visible.push_back({id, p, o});
    }
    return out;
}
// Trusted observation from observe(); policies do not receive State.
inline std::vector<Action> actions(Observation const& o) {
    std::vector<Action> out;
    if (!valid(o.viewer) || !valid(o.priority) || o.turn >= turn_limit || o.viewer != o.priority) return out;
    out.push_back({o.viewer, ActionKind::pass, Entity{0}});
    for (auto const& v : o.visible)
        if (v.id.value < 4 && owner(v.id) == o.viewer && v.owner == o.viewer && v.object.zone == Zone::private_area)
            out.push_back({o.viewer, ActionKind::reveal, v.id});
    return out;
}
inline State apply(State const& input, Action a) {
    if (!legal(input, a)) throw std::invalid_argument("illegal action");
    auto s = input;
    if (a.kind == ActionKind::reveal) {
        s.objects[a.target.value].zone = Zone::public_area;
        s.passed = false;
        s.priority = Player{1 - a.actor.value};
    } else if (s.passed) {
        ++s.turn;
        s.passed = false;
        s.priority = Player{s.turn == turn_limit ? 0u : s.turn % 2u};
    } else {
        s.passed = true;
        s.priority = Player{1 - a.actor.value};
    }
    return s;
}
} // namespace ctr::kernel
