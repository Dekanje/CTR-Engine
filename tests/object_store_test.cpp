#include "ctr/object_store.hpp"
#include <array>
#include <iostream>
namespace s = ctr::storage;
void check(bool ok) { if (!ok) throw std::runtime_error("object store check"); }
template<class F> void rejects(F f) {
    try { f(); } catch (std::invalid_argument const&) { return; }
    throw std::runtime_error("expected storage rejection");
}
s::Snapshot fixture() {
    return {7, 0, 2, {{s::ObjectId{1}, s::TypeId{11}, s::Principal{0}},
                      {s::ObjectId{2}, s::TypeId{12}, s::Principal{1}},
                      {s::ObjectId{3}, s::TypeId{13}, s::Principal{0}}},
        {{s::ContainerId{10}, std::nullopt, s::Visibility::everyone, false, {}},
         {s::ContainerId{20}, s::Principal{0}, s::Visibility::owner_only, true, {}},
         {s::ContainerId{30}, std::nullopt, s::Visibility::authority_only, false, {}}}};
}
int main() {
    unsigned placements = 0, transactions = 0, projections = 0;
    // Every assignment of three objects to three containers, with every
    // global insertion order. Test every subset of simultaneous transfers
    // to either alternative destination, in every request order.
    for (unsigned assignment = 0; assignment < 27; ++assignment) {
        std::array<unsigned,3> loc{assignment%3, assignment/3%3, assignment/9};
        std::array<unsigned,3> order{0,1,2};
        do {
            auto st = fixture();
            for (auto j : order) st.containers[loc[j]].order.push_back(st.objects[j].id);
            check(s::valid(st)); ++placements;
            for (unsigned viewer=0; viewer<2; ++viewer) {
                auto changed = st;
                for (unsigned j=0;j<3;++j)
                    if (loc[j]==2 || (loc[j]==1 && viewer==1))
                        changed.objects[j].type.value += 100;
                for (unsigned c=0;c<3;++c)
                    if (c==2 || (c==1 && viewer==1))
                        std::reverse(changed.containers[c].order.begin(),changed.containers[c].order.end());
                const auto obs=s::observe(st,s::Principal{viewer});
                check(obs==s::observe(changed,s::Principal{viewer}));
                check(obs.containers[0].contents.has_value() &&
                      obs.containers[0].count==st.containers[0].order.size());
                check(obs.containers[1].contents.has_value()==(viewer==0) &&
                      obs.containers[1].count==st.containers[1].order.size());
                check(!obs.containers[2].contents && !obs.containers[2].count);
                ++projections;
            }
            for (unsigned choice=1; choice<27; ++choice) {
                const std::array<unsigned,3> step{choice%3,choice/3%3,choice/9};
                std::array<unsigned,3> sequence{0,1,2};
                do {
                    s::Transaction tx{st.session, st.revision, {}};
                    for (auto j:sequence) if (step[j]) tx.transfers.push_back(
                        {st.objects[j].id,st.containers[loc[j]].id,
                         st.containers[(loc[j]+step[j])%3].id});
                    // Independent oracle: reconstruct order per destination
                    // from original survivors and explicit request sequence.
                    auto expected=st; ++expected.revision;
                    for (unsigned c=0;c<3;++c) {
                        auto& dest=expected.containers[c].order; dest.clear();
                        for (auto j:order) if (loc[j]==c && !step[j]) dest.push_back(st.objects[j].id);
                        for (auto j:sequence) if (step[j] && (loc[j]+step[j])%3==c)
                            dest.push_back(st.objects[j].id);
                    }
                    const auto before=st;
                    auto result=s::apply(st,tx);
                    check(result==expected && st==before && s::valid(result)); ++transactions;
                    rejects([&]{ (void)s::apply(result,tx); });
                } while(std::next_permutation(sequence.begin(),sequence.end()));
            }
        } while(std::next_permutation(order.begin(),order.end()));
    }
    auto st=fixture();
    st.containers[0].order={s::ObjectId{1},s::ObjectId{2},s::ObjectId{3}};
    check(s::valid(st));
    const auto before=st;
    s::Transaction tx{7,0,{{s::ObjectId{1},s::ContainerId{10},s::ContainerId{20}}}};
    auto bad=tx; bad.session=8; rejects([&]{(void)s::apply(st,bad);});
    bad=tx; bad.revision=1; rejects([&]{(void)s::apply(st,bad);});
    bad=tx; bad.transfers.clear(); rejects([&]{(void)s::apply(st,bad);});
    bad=tx; bad.transfers.push_back(bad.transfers.front()); rejects([&]{(void)s::apply(st,bad);});
    bad=tx; bad.transfers.push_back({s::ObjectId{9},s::ContainerId{10},s::ContainerId{20}});
    rejects([&]{(void)s::apply(st,bad);});
    bad=tx; bad.transfers[0].to=s::ContainerId{10}; rejects([&]{(void)s::apply(st,bad);});
    bad=tx; bad.transfers[0].from=s::ContainerId{30}; rejects([&]{(void)s::apply(st,bad);});
    bad=tx; bad.transfers[0].to=s::ContainerId{99}; rejects([&]{(void)s::apply(st,bad);});
    bad=tx; bad.transfers.resize(s::max_transfers+1,bad.transfers.front());
    rejects([&]{(void)s::apply(st,bad);});
    check(st==before);
    auto overflow=st; overflow.revision=std::numeric_limits<std::uint64_t>::max();
    bad=tx; bad.revision=overflow.revision; rejects([&]{(void)s::apply(overflow,bad);});
    rejects([&]{(void)s::observe(st,s::Principal{2});});
    auto invalid=st;
    auto reject_state=[&]{ check(!s::valid(invalid)); rejects([&]{(void)s::observe(invalid,s::Principal{0});});
        rejects([&]{(void)s::apply(invalid,tx);}); invalid=st; };
    invalid.session=0; reject_state();
    invalid.principals=0; reject_state();
    invalid.principals=65; reject_state();
    invalid.objects[0].id=s::ObjectId{0}; reject_state();
    invalid.objects[0].id=invalid.objects[1].id; reject_state();
    invalid.objects[0].type=s::TypeId{0}; reject_state();
    invalid.objects[0].owner=s::Principal{2}; reject_state();
    invalid.containers[0].id=s::ContainerId{0}; reject_state();
    invalid.containers[0].id=invalid.containers[1].id; reject_state();
    invalid.containers[1].owner.reset(); reject_state();
    invalid.containers[1].owner=s::Principal{2}; reject_state();
    invalid.containers[1].visibility=static_cast<s::Visibility>(255); reject_state();
    invalid.containers[0].order.pop_back(); reject_state();
    invalid.containers[0].order[0]=s::ObjectId{99}; reject_state();
    invalid.containers[0].order[0]=invalid.containers[0].order[1]; reject_state();
    invalid.containers[1].order.push_back(s::ObjectId{1}); reject_state();
    invalid.objects.resize(s::max_objects+1,invalid.objects.front()); reject_state();
    invalid.containers.resize(s::max_containers+1,invalid.containers.front()); reject_state();
    invalid.containers.clear(); reject_state();
    check(placements==162 && transactions==25272 && projections==324);
    std::cout<<"object-store-v1:"<<placements<<" placements:"<<transactions<<" transactions:"<<projections<<" projections\n";
}
