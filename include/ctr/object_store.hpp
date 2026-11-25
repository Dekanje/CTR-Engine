#pragma once
#include "ctr/core.hpp"
#include <algorithm>
#include <limits>
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// Generic ordered object storage. No game-specific legality or transitions.
namespace ctr::storage {
struct ObjectTag;
struct TypeTag;
struct ContainerTag;
struct PrincipalTag;
using ObjectId = Id<ObjectTag>;
using TypeId = Id<TypeTag>;
using ContainerId = Id<ContainerTag>;
using Principal = Id<PrincipalTag>;

enum class Visibility : std::uint8_t { everyone, owner_only, authority_only };
struct Object {
    ObjectId id;
    TypeId type;
    Principal owner;
    bool operator==(const Object&) const = default;
};
struct Container {
    ContainerId id;
    std::optional<Principal> owner;
    Visibility visibility;
    bool disclose_count;
    std::vector<ObjectId> order;
    bool operator==(const Container&) const = default;
};
struct Snapshot {
    std::uint64_t session;
    std::uint64_t revision;
    std::uint32_t principals;
    std::vector<Object> objects;
    std::vector<Container> containers;
    bool operator==(const Snapshot&) const = default;
};
inline constexpr std::size_t max_objects = 4096, max_containers = 256;
inline constexpr std::size_t max_transfers = 4096;
inline bool valid(Snapshot const& s) {
    if (!s.session || !s.principals || s.principals > 64 ||
        s.objects.size() > max_objects || s.containers.size() > max_containers ||
        s.containers.empty()) return false;
    std::unordered_set<std::uint32_t> ids, containers, located;
    for (auto const& o : s.objects) {
        if (!o.id.value || !o.type.value || o.owner.value >= s.principals ||
            !ids.insert(o.id.value).second) return false;
    }
    for (auto const& c : s.containers) {
        if (!c.id.value || !containers.insert(c.id.value).second ||
            (c.owner && c.owner->value >= s.principals) ||
            c.order.size() > s.objects.size()) return false;
        switch (c.visibility) {
            case Visibility::everyone: break;
            case Visibility::owner_only: if (!c.owner) return false; break;
            case Visibility::authority_only: break;
            default: return false;
        }
        for (auto id : c.order)
            if (!ids.contains(id.value) || !located.insert(id.value).second) return false;
    }
    return located.size() == ids.size();
}
struct ContainerView {
    ContainerId id;
    std::optional<std::size_t> count;
    std::optional<std::vector<Object>> contents;
    bool operator==(const ContainerView&) const = default;
};
struct Observation {
    std::uint64_t session;
    std::uint64_t revision;
    Principal viewer;
    std::vector<ContainerView> containers;
    bool operator==(const Observation&) const = default;
};
// Container identities and their existence are public metadata. Hidden object
// identities, owners, types and order are never emitted by this projection.
inline Observation observe(Snapshot const& s, Principal viewer) {
    if (!valid(s) || viewer.value >= s.principals) throw std::invalid_argument("storage observation");
    std::unordered_map<std::uint32_t, Object const*> lookup;
    for (auto const& o : s.objects) lookup.emplace(o.id.value, &o);
    Observation out{s.session, s.revision, viewer, {}};
    for (auto const& c : s.containers) {
        const bool visible = c.visibility == Visibility::everyone ||
            (c.visibility == Visibility::owner_only && c.owner == viewer);
        ContainerView v{c.id, std::nullopt, std::nullopt};
        if (visible || c.disclose_count) v.count = c.order.size();
        if (visible) {
            v.contents.emplace();
            for (auto id : c.order) v.contents->push_back(*lookup.at(id.value));
        }
        out.containers.push_back(std::move(v));
    }
    return out;
}
struct Transfer {
    ObjectId object;
    ContainerId from;
    ContainerId to;
};
struct Transaction {
    std::uint64_t session;
    std::uint64_t revision;
    std::vector<Transfer> transfers;
};
// Each object is transferred at most once, from its original container.
// Survivors retain their relative order; incoming objects append in request order.
// This is an authority-only storage operation, not a player action or legality check.
inline Snapshot apply(Snapshot const& input, Transaction const& tx) {
    if (!valid(input) || tx.session != input.session || tx.revision != input.revision ||
        input.revision == std::numeric_limits<std::uint64_t>::max() ||
        tx.transfers.empty() || tx.transfers.size() > max_transfers)
        throw std::invalid_argument("storage transaction identity or size");
    std::unordered_map<std::uint32_t, std::size_t> ci, oi;
    for (std::size_t j = 0; j < input.containers.size(); ++j) {
        ci.emplace(input.containers[j].id.value, j);
        for (auto id : input.containers[j].order) oi.emplace(id.value, j);
    }
    std::unordered_set<std::uint32_t> moved;
    for (auto const& t : tx.transfers) {
        const auto source = ci.find(t.from.value), dest = ci.find(t.to.value);
        const auto object = oi.find(t.object.value);
        if (source == ci.end() || dest == ci.end() || source == dest ||
            object == oi.end() || object->second != source->second ||
            !moved.insert(t.object.value).second)
            throw std::invalid_argument("storage transfer");
    }
    auto next = input;
    for (auto& c : next.containers)
        std::erase_if(c.order, [&](ObjectId id) { return moved.contains(id.value); });
    for (auto const& t : tx.transfers)
        next.containers[ci.at(t.to.value)].order.push_back(t.object);
    ++next.revision;
    if (!valid(next)) throw std::logic_error("storage invariant");
    return next;
}
} // namespace ctr::storage
