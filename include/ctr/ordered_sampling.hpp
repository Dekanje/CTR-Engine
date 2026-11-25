#pragma once
#include "ctr/object_store.hpp"

// Independent ordered sampling and exchange primitives; no format-specific rules.
namespace ctr::sampling {
using namespace storage;
struct Stamp {
    std::uint64_t session, revision;
};
inline void require(Snapshot const& s, Stamp stamp) {
    if (!valid(s) || s.session != stamp.session || s.revision != stamp.revision ||
        s.revision == std::numeric_limits<std::uint64_t>::max())
        throw std::invalid_argument("sampling snapshot or stamp");
}
inline std::size_t index(Snapshot const& s, ContainerId id) {
    for (std::size_t i=0; i<s.containers.size(); ++i)
        if (s.containers[i].id == id) return i;
    throw std::invalid_argument("sampling container");
}
struct Permutation {
    Stamp stamp;
    ContainerId container;
    std::vector<std::size_t> choices;
};
// Explicit Fisher-Yates choices in descending prefix-size order.
// Only authority code receives or replays this record.
inline Snapshot permute(Snapshot const& s, Permutation const& p) {
    require(s,p.stamp);
    const auto k=index(s,p.container);
    const auto n=s.containers[k].order.size();
    if (p.choices.size() != (n ? n-1 : 0))
        throw std::invalid_argument("permutation length");
    for (std::size_t j=0;j<p.choices.size();++j)
        if (p.choices[j]>=n-j) throw std::invalid_argument("permutation choice");
    auto next=s;
    auto& order=next.containers[k].order;
    for (std::size_t j=0;j<p.choices.size();++j)
        std::swap(order[n-j-1],order[p.choices[j]]);
    ++next.revision;
    if (!valid(next)) throw std::logic_error("permutation invariant");
    return next;
}
inline Permutation sample(Snapshot const& s, Stamp stamp, ContainerId id, Random& rng) {
    require(s,stamp);
    const auto n=s.containers[index(s,id)].order.size();
    Permutation p{stamp,id,{}};
    p.choices.reserve(n ? n-1 : 0);
    for (auto remaining=n;remaining>1;--remaining)
        p.choices.push_back(static_cast<std::size_t>(bounded(rng,remaining)));
    return p;
}
struct Pair {
    Principal owner;
    ContainerId pool, collection;
};
inline std::pair<std::size_t,std::size_t> pair_indices(Snapshot const& s, Pair p) {
    const auto a=index(s,p.pool), b=index(s,p.collection);
    const auto& pool=s.containers[a];
    const auto& collection=s.containers[b];
    if (a==b || p.owner.value>=s.principals || pool.owner!=p.owner ||
        collection.owner!=p.owner || pool.visibility!=Visibility::authority_only ||
        collection.visibility!=Visibility::owner_only)
        throw std::invalid_argument("sampling pair");
    std::unordered_set<std::uint32_t> owned;
    for (auto const& o:s.objects) if (o.owner==p.owner) owned.insert(o.id.value);
    for (auto const* c:{&pool,&collection})
        for (auto id:c->order)
            if (!owned.contains(id.value)) throw std::invalid_argument("sampling ownership");
    return {a,b};
}
// Index zero is the front of an ordered pool. Exact count or rejection;
// no implicit short draw or depletion policy.
inline Snapshot take(Snapshot const& s, Stamp stamp, Pair p, std::size_t count) {
    require(s,stamp);
    const auto [a,b]=pair_indices(s,p);
    (void)b;
    const auto& pool=s.containers[a].order;
    if (count>pool.size()) throw std::invalid_argument("sampling count");
    if (!count) { auto next=s; ++next.revision; return next; }
    Transaction tx{stamp.session,stamp.revision,{}};
    for (std::size_t j=0;j<count;++j) tx.transfers.push_back({pool[j],p.pool,p.collection});
    return apply(s,tx);
}
// Replacement objects come from the original pool; returned objects are
// appended in the caller-specified order. All transfers commit together.
// Caller must supply the permitted maximum, and enforce any phase restrictions.
inline Snapshot exchange(Snapshot const& s, Stamp stamp, Pair p,
                         std::span<const ObjectId> returned, std::size_t maximum) {
    require(s,stamp);
    const auto [a,b]=pair_indices(s,p);
    const auto& pool=s.containers[a].order;
    const auto& collection=s.containers[b].order;
    if (maximum>max_objects || returned.size()>maximum ||
        returned.size()>pool.size() || returned.size()>collection.size() ||
        returned.size()>max_transfers/2)
        throw std::invalid_argument("exchange count");
    if (returned.empty()) { auto next=s; ++next.revision; return next; }
    Transaction tx{stamp.session,stamp.revision,{}};
    for (std::size_t j=0;j<returned.size();++j)
        tx.transfers.push_back({pool[j],p.pool,p.collection});
    for (auto id:returned) tx.transfers.push_back({id,p.collection,p.pool});
    return apply(s,tx);
}
} // namespace ctr::sampling
