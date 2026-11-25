#include "ctr/ordered_sampling.hpp"
#include <functional>
#include <iostream>
#include <set>
namespace s=ctr::storage;
namespace q=ctr::sampling;
void check(bool ok) {if(!ok) throw std::runtime_error("sampling check");}
template<class F> void rejects(F f) {
    try { f(); } catch(std::invalid_argument const&) {return;}
    throw std::runtime_error("expected sampling rejection");
}
s::Snapshot fixture(unsigned n) {
    s::Snapshot out{9,0,2,{},
      {{s::ContainerId{1},s::Principal{0},s::Visibility::authority_only,true,{}},
       {s::ContainerId{2},s::Principal{0},s::Visibility::owner_only,true,{}}}};
    for(unsigned j=1;j<=n;++j) {
        out.objects.push_back({s::ObjectId{j},s::TypeId{j},s::Principal{0}});
        out.containers[0].order.push_back(s::ObjectId{j});
    }
    return out;
}
q::Stamp stamp(s::Snapshot const& s) {return {s.session,s.revision};}
const q::Pair pair{s::Principal{0},s::ContainerId{1},s::ContainerId{2}};
std::vector<unsigned> values(std::vector<s::ObjectId> const& ids) {
    std::vector<unsigned> out; for(auto id:ids) out.push_back(id.value); return out;
}
int main() {
    unsigned permutations=0, exchanges=0, takes=0, random_cases=0;
    for(unsigned n=0;n<=7;++n) {
        const auto st=fixture(n);
        q::Permutation p{stamp(st),pair.pool,{}};
        std::set<std::vector<unsigned>> actual,expected;
        auto sorted=values(st.containers[0].order);
        do {expected.insert(sorted);} while(std::next_permutation(sorted.begin(),sorted.end()));
        std::function<void(unsigned)> enumerate=[&](unsigned left){
            if(left<=1) {
                const auto next=q::permute(st,p);
                check(s::valid(next)&&next.revision==1);
                check(actual.insert(values(next.containers[0].order)).second);
                check(s::observe(st,s::Principal{0}).containers==s::observe(next,s::Principal{0}).containers);
                rejects([&]{(void)q::permute(next,p);});
                ++permutations; return;
            }
            for(unsigned j=0;j<left;++j) {p.choices.push_back(j); enumerate(left-1);p.choices.pop_back();}
        };
        enumerate(n); check(actual==expected);
        for(unsigned count=0;count<=n;++count) {
            const auto next=q::take(st,stamp(st),pair,count);
            auto all=values(st.containers[0].order);
            check(values(next.containers[0].order)==std::vector<unsigned>(all.begin()+count,all.end()));
            check(values(next.containers[1].order)==std::vector<unsigned>(all.begin(),all.begin()+count));
            check(next.revision==1&&s::valid(next)); ++takes;
        }
        rejects([&]{(void)q::take(st,stamp(st),pair,n+1);});
    }
    // All ordered subsets of the first three of seven items (0..3 selections).
    const auto st=q::take(fixture(7),{9,0},pair,3);
    const auto before=st;
    std::vector<s::ObjectId> chosen;
    std::function<void()> visit=[&] {
        auto next=q::exchange(st,stamp(st),pair,chosen,3);
        auto pool=values(st.containers[0].order), hand=values(st.containers[1].order);
        std::vector<unsigned> exp_pool(pool.begin()+chosen.size(),pool.end());
        std::vector<unsigned> exp_hand;
        for(auto x:hand) if(std::find(chosen.begin(),chosen.end(),s::ObjectId{x})==chosen.end()) exp_hand.push_back(x);
        exp_hand.insert(exp_hand.end(),pool.begin(),pool.begin()+chosen.size());
        for(auto id:chosen) exp_pool.push_back(id.value);
        check(values(next.containers[0].order)==exp_pool&&values(next.containers[1].order)==exp_hand);
        check(st==before&&s::valid(next)&&next.revision==2);
        check(s::observe(next,s::Principal{1}).containers==s::observe(st,s::Principal{1}).containers);
        rejects([&]{(void)q::exchange(next,stamp(st),pair,chosen,3);}); ++exchanges;
        for(auto id:st.containers[1].order)
            if(std::find(chosen.begin(),chosen.end(),id)==chosen.end()) {
                chosen.push_back(id);visit();chosen.pop_back();
            }
    };
    visit();
    for(unsigned seed=0;seed<64;++seed) {
        ctr::Random a(seed,ctr::Stream::gameplay,17),b(seed,ctr::Stream::gameplay,17);
        const auto initial=fixture(39);
        const auto p=q::sample(initial,stamp(initial),pair.pool,a), r=q::sample(initial,stamp(initial),pair.pool,b);
        check(p.choices==r.choices);
        const auto shuffled=q::permute(initial,p);
        check(shuffled==q::permute(initial,r));
        const auto opened=q::take(shuffled,stamp(shuffled),pair,4);
        const auto hand=opened.containers[1].order;
        for(unsigned n=0;n<=2;++n) {
            const auto next=q::exchange(opened,stamp(opened),pair,std::span(hand).first(n),2);
            check(next.containers[1].order.size()==4&&next.containers[0].order.size()==35);
            for(unsigned j=0;j<n;++j) check(next.containers[0].order[35-n+j]==hand[j]);
            ++random_cases;
        }
    }
    const auto initial=fixture(7);
    auto p=q::Permutation{stamp(initial),pair.pool,{0,0,0,0,0,0}};
    auto bad=p;bad.choices.pop_back();rejects([&]{(void)q::permute(initial,bad);});
    bad=p;bad.choices[5]=2;rejects([&]{(void)q::permute(initial,bad);});
    bad=p;bad.stamp.session=10;rejects([&]{(void)q::permute(initial,bad);});
    bad=p;bad.container=s::ContainerId{99};rejects([&]{(void)q::permute(initial,bad);});
    std::array duplicate{s::ObjectId{1},s::ObjectId{1}};
    std::array foreign{s::ObjectId{4}};
    std::array unknown{s::ObjectId{999}};
    rejects([&]{(void)q::exchange(st,stamp(st),pair,duplicate,3);});
    rejects([&]{(void)q::exchange(st,stamp(st),pair,foreign,3);});
    rejects([&]{(void)q::exchange(st,stamp(st),pair,unknown,3);});
    rejects([&]{(void)q::exchange(st,stamp(st),pair,duplicate,1);});
    auto other=pair;other.owner=s::Principal{1};rejects([&]{(void)q::take(st,stamp(st),other,1);});
    other=pair;other.collection=pair.pool;rejects([&]{(void)q::take(st,stamp(st),other,0);});
    auto changed=st;changed.objects[0].owner=s::Principal{1};rejects([&]{(void)q::take(changed,stamp(changed),pair,0);});
    changed=st;changed.containers[0].visibility=s::Visibility::everyone;rejects([&]{(void)q::take(changed,stamp(changed),pair,0);});
    changed=st;changed.revision=std::numeric_limits<std::uint64_t>::max();rejects([&]{(void)q::take(changed,stamp(changed),pair,0);});
    const auto depleted=q::take(initial,stamp(initial),pair,7);
    std::array one{s::ObjectId{1}};
    rejects([&]{(void)q::exchange(depleted,stamp(depleted),pair,one,1);});
    check(st==before);
    check(permutations==5914&&takes==36&&exchanges==16&&random_cases==192);
    std::cout<<"ordered-sampling-v1:"<<permutations<<" permutations:"<<takes<<" takes:"<<exchanges<<" ordered exchanges:"<<random_cases<<" seeded cases\n";
}
