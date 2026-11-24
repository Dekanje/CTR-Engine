#include <array>
#include <cstdint>
#include <iostream>
#include <span>

// Synthetic build/IPC probe only; not a game rule or a simulation.
constexpr std::uint32_t sum(std::span<const std::uint32_t> values) {
    std::uint32_t result = 0;
    for (const auto value : values) result += value;
    return result;
}

int main(int argc, char**) {
    if (argc != 1) return 2;
    constexpr std::array<std::uint32_t, 3> fixture{7, 11, 24};
    static_assert(sum(fixture) == 42);
    std::cout << "ctr-probe-v1:" << sum(fixture) << '\n';
    return std::cout ? 0 : 1;
}
