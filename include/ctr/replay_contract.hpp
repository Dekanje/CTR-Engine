#pragma once
#include "ctr/integrated.hpp"

// Authority-only replay envelope. Identity tags are not cryptographic digests.
namespace ctr::replay_contract {
using Identity = std::array<std::uint8_t, 8>;
inline constexpr Identity integrated_v1{67,84,82,73,1,1,1,1};
struct Envelope {
    Identity identity;
    integrated::StateBytes initial;
    std::vector<integrated::ActionBytes> actions;
    integrated::StateBytes final_state;
};
inline integrated::State verify(Envelope const& log) {
    if (log.identity != integrated_v1) throw std::invalid_argument("replay identity");
    const auto expected = integrated::decode_state(log.final_state);
    const auto actual = integrated::replay(log.initial, log.actions);
    if (actual != expected) throw std::invalid_argument("replay final state mismatch");
    return actual;
}
} // namespace ctr::replay_contract
