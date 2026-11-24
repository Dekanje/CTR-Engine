#pragma once
#include <algorithm>
#include <cstdint>
#include <span>
#include <stdexcept>
#include <vector>

// Generic bounded integer modifier contract; not official game semantics.
namespace ctr::modifiers {
enum class Operation : std::uint8_t { set, add, multiply };
struct Rule {
    std::uint32_t id;
    unsigned layer;
    unsigned required_mask;
    Operation operation;
    int operand;
};
inline unsigned evaluate(unsigned base, unsigned active_mask, std::span<const Rule> input) {
    if (base > 100 || active_mask > 15 || input.size() > 64)
        throw std::invalid_argument("modifier input");
    std::vector<Rule> rules(input.begin(), input.end());
    std::sort(rules.begin(), rules.end(), [](auto a, auto b) { return a.id < b.id; });
    for (std::size_t i = 0; i < rules.size(); ++i) {
        const auto r = rules[i];
        if (r.id == 0 || (i && rules[i-1].id == r.id) || r.layer > 7 || r.required_mask > 15)
            throw std::invalid_argument("modifier identity");
        switch (r.operation) {
            case Operation::set: if (r.operand >= 0 && r.operand <= 100) continue; break;
            case Operation::add: if (r.operand >= -100 && r.operand <= 100) continue; break;
            case Operation::multiply: if (r.operand >= 0 && r.operand <= 4) continue; break;
        }
        throw std::invalid_argument("modifier operation");
    }
    std::sort(rules.begin(), rules.end(), [](auto a, auto b) {
        return a.layer != b.layer ? a.layer < b.layer : a.id < b.id;
    });
    int value = static_cast<int>(base);
    for (const auto r : rules) {
        if ((active_mask & r.required_mask) != r.required_mask) continue;
        switch (r.operation) {
            case Operation::set: value = r.operand; break;
            case Operation::add: value += r.operand; break;
            case Operation::multiply: value *= r.operand; break;
        }
        if (value < 0 || value > 100) throw std::invalid_argument("modifier range");
    }
    return static_cast<unsigned>(value);
}
} // namespace ctr::modifiers
