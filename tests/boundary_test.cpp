#include "ctr/replay_contract.hpp"
#include <iostream>
namespace k = ctr::kernel;
namespace i = ctr::integrated;
namespace r = ctr::replay_contract;
void check(bool ok) { if (!ok) throw std::runtime_error("boundary check failed"); }
template<class F> void rejects(F f) {
    try { f(); } catch (const std::invalid_argument&) { return; }
    throw std::runtime_error("expected rejection");
}
int main() {
    unsigned projections = 0, mutations = 0;
    for (unsigned mask=0; mask<16; ++mask) for (unsigned viewer=0; viewer<2; ++viewer)
    for (unsigned priority=0; priority<2; ++priority) {
        i::State s; s.board.priority=k::Player{priority}; s.resources.balance={10,10};
        for (unsigned j=0;j<4;++j) s.board.objects[j].zone=(mask&(1u<<j))?k::Zone::public_area:k::Zone::private_area;
        const auto obs=i::observe(s,k::Player{viewer});
        check(k::valid(obs.board)); (void)i::actions(obs); ++projections;
        auto bad=obs;
        auto reject=[&]{ check(!k::valid(bad.board)); rejects([&]{ (void)i::actions(bad); }); ++mutations; bad=obs; };
        bad.board.viewer=k::Player{2}; reject();
        bad.board.priority=k::Player{2}; reject();
        bad.board.turn=4; reject();
        bad.board.turn=3; bad.board.passed=true; reject();
        bad.board.private_counts[viewer]=3; reject();
        bad.board.visible.push_back(bad.board.visible.front()); reject();
        bad.board.visible.front().id=k::Entity{4}; reject();
        bad.board.visible.front().owner=k::Player{2}; reject();
        bad.board.visible.front().object.zone=static_cast<k::Zone>(255); reject();
        auto own=std::find_if(bad.board.visible.begin(),bad.board.visible.end(),[&](auto v){return v.owner.value==viewer;});
        bad.board.visible.erase(own); reject();
        std::swap(bad.board.visible[0],bad.board.visible[1]); reject();
        const auto enemy=std::find_if(bad.board.visible.begin(),bad.board.visible.end(),[&](auto v){return v.owner.value!=viewer;});
        if (enemy!=bad.board.visible.end()) { enemy->object.zone=k::Zone::private_area; reject(); }
        bad.resources.balance[0]=101; rejects([&]{ (void)i::actions(bad); });
        const k::Action wrong{k::Player{1-viewer},k::ActionKind::pass,k::Entity{0}};
        rejects([&]{ (void)i::payment(obs,wrong); });
    }
    i::State s; s.resources.balance={10,10};
    const k::Action a{k::Player{0},k::ActionKind::reveal,k::Entity{0}};
    const auto final=i::apply(s,a).state;
    r::Envelope log{r::integrated_v1,i::encode(s),{i::encode(a)},i::encode(final)};
    check(r::verify(log)==final);
    for (unsigned j=0;j<log.identity.size();++j) {
        auto bad=log; bad.identity[j]^=1; rejects([&]{ (void)r::verify(bad); });
    }
    auto bad=log; bad.final_state=i::encode(s); rejects([&]{ (void)r::verify(bad); });
    bad=log; bad.actions.clear(); rejects([&]{ (void)r::verify(bad); });
    bad=log; bad.actions.resize(33); rejects([&]{ (void)r::verify(bad); });
    bad=log; bad.final_state[0]=2; rejects([&]{ (void)r::verify(bad); });
    check(projections==64 && mutations==752);
    std::cout << "boundary-v1:" << projections << " projections:" << mutations << " mutations\n";
}
