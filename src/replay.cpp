#include "ctr/replay_contract.hpp"
#include <algorithm>
#include <iostream>

// One bounded authority-only binary request, no game-specific semantics.
int main() {
    namespace r = ctr::replay_contract;
    namespace i = ctr::integrated;
    constexpr std::size_t fixed = 8 + 26 + 1 + 26;
    constexpr std::size_t maximum = fixed + 32 * 4;
    std::array<std::uint8_t, maximum> input{};
    std::size_t size = 0;
    for (char c; std::cin.get(c);) {
        if (size == input.size()) return 2;
        input[size++] = static_cast<std::uint8_t>(c);
    }
    if (std::cin.bad() || !std::cin.eof() || size < fixed) return 2;
    const unsigned count = input[34];
    if (count > 32 || size != fixed + 4 * count) return 2;
    try {
        r::Envelope log{};
        std::copy_n(input.begin(), 8, log.identity.begin());
        std::copy_n(input.begin() + 8, 26, log.initial.begin());
        for (unsigned j = 0; j < count; ++j) {
            i::ActionBytes action{};
            std::copy_n(input.begin() + 35 + 4 * j, 4, action.begin());
            log.actions.push_back(action);
        }
        std::copy_n(input.begin() + 35 + 4 * count, 26, log.final_state.begin());
        const auto result = i::encode(r::verify(log));
        std::cout.write(reinterpret_cast<const char*>(result.data()), result.size());
        std::cout.flush();
        return std::cout ? 0 : 4;
    } catch (const std::invalid_argument&) {
        return 3;
    } catch (...) {
        return 4;
    }
}
