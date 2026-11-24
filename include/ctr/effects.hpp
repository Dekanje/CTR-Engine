#pragma once
#include "ctr/core.hpp"
#include <algorithm>
#include <deque>
#include <optional>
#include <vector>

// Synthetic resolution contract, independent of game semantics.
namespace ctr::effects {
enum class Kind : std::uint8_t { credit, debit };
struct Event {
    Kind kind;
    std::uint8_t target;
    std::uint8_t amount;
    bool operator==(const Event&) const = default;
};
struct State {
    std::array<unsigned, 2> balance{};
    bool operator==(const State&) const = default;
};
struct Replacement {
    unsigned id;
    Event match;
    std::optional<Event> output; // empty cancels the event
};
struct Trigger {
    unsigned id;
    Event match;
    Event output;
};
struct Program {
    unsigned version = 1;
    std::vector<Replacement> replacements;
    std::vector<Trigger> triggers;
};
struct Limits {
    unsigned events = 64;
    unsigned rewrites = 16;
    unsigned pending = 64;
};
struct Record {
    Event input;
    std::vector<unsigned> replacements;
    std::optional<Event> applied;
    std::vector<unsigned> triggers;
    bool operator==(const Record&) const = default;
};
struct Result {
    State state;
    std::vector<Record> trace;
    bool operator==(const Result&) const = default;
};
inline bool valid(Event e) {
    return (e.kind == Kind::credit || e.kind == Kind::debit) &&
           e.target < 2 && e.amount > 0 && e.amount <= 100;
}
inline bool valid(State s) { return s.balance[0] <= 100 && s.balance[1] <= 100; }
inline void require(bool ok, const char* reason) {
    if (!ok) throw std::invalid_argument(reason);
}
template<class Rule> void order(std::vector<Rule>& rules) {
    std::sort(rules.begin(), rules.end(), [](auto const& a, auto const& b) { return a.id < b.id; });
    for (std::size_t i = 0; i < rules.size(); ++i)
        require(rules[i].id != 0 && (i == 0 || rules[i-1].id != rules[i].id), "rule id");
}
// Only returns committed state and trace after the entire transaction succeeds.
inline Result resolve(State initial, std::span<const Event> input, Program const& program, Limits lim = {}) {
    require(valid(initial) && program.version == 1, "state or version");
    require(lim.events > 0 && lim.events <= 256 && lim.rewrites > 0 && lim.rewrites <= 64 &&
            lim.pending > 0 && lim.pending <= 256, "limits");
    require(input.size() <= lim.pending && input.size() <= lim.events &&
            program.replacements.size() <= 64 && program.triggers.size() <= 64, "input size");
    auto replacements = program.replacements;
    auto triggers = program.triggers;
    order(replacements); order(triggers);
    for (auto const& r : replacements)
        require(valid(r.match) && (!r.output || valid(*r.output)), "replacement event");
    for (auto const& t : triggers) require(valid(t.match) && valid(t.output), "trigger event");
    for (auto e : input) require(valid(e), "input event");
    std::deque<Event> queue(input.begin(), input.end());
    Result result{initial, {}};
    while (!queue.empty()) {
        require(result.trace.size() < lim.events, "event budget");
        const Event start = queue.front(); queue.pop_front();
        Record record{start, {}, start, {}};
        std::vector<Event> seen{start};
        while (record.applied) {
            auto r = std::find_if(replacements.begin(), replacements.end(), [&](auto const& x) {
                return x.match == *record.applied;
            });
            if (r == replacements.end()) break;
            require(record.replacements.size() < lim.rewrites, "rewrite budget");
            record.replacements.push_back(r->id);
            record.applied = r->output;
            if (record.applied) {
                require(std::find(seen.begin(), seen.end(), *record.applied) == seen.end(), "replacement cycle");
                seen.push_back(*record.applied);
            }
        }
        if (record.applied) {
            const auto e = *record.applied;
            auto& balance = result.state.balance[e.target];
            if (e.kind == Kind::credit) {
                require(e.amount <= 100 - balance, "overflow"); balance += e.amount;
            } else {
                require(e.amount <= balance, "underflow"); balance -= e.amount;
            }
            for (auto const& t : triggers) if (t.match == e) {
                require(queue.size() < lim.pending, "pending budget");
                queue.push_back(t.output); record.triggers.push_back(t.id);
            }
        }
        result.trace.push_back(std::move(record));
    }
    return result;
}
} // namespace ctr::effects
