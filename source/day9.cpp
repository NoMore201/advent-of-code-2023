#include "day9.hpp"
#include "string.hpp"
#include "utils.hpp"

#include <gsl/assert>

#include <cstdint>
#include <map>
#include <numeric>
#include <string_view>
#include <utility>

namespace {

using Sequence = std::vector<int>;
using Size = std::size_t;

class SequenceTree {
public:

    using Iterator = std::vector<Sequence>::const_iterator;
    using ReverseIterator = std::vector<Sequence>::const_reverse_iterator;

private:
    std::vector<Sequence> m_tree;

public:
    static bool is_terminating_sequence(const Sequence &sequence) {
        return std::all_of(sequence.begin(), sequence.end(), [](int number) { return number == 0; });
    }

    Iterator begin() const noexcept { return m_tree.cbegin(); }
    Iterator end() const noexcept { return m_tree.cbegin(); }

    ReverseIterator rbegin() const noexcept { return m_tree.rbegin(); }
    ReverseIterator rend() const noexcept { return m_tree.rend(); }

    explicit SequenceTree(Sequence sequence) {
        Expects(sequence.size() > 1);
        m_tree.push_back(std::move(sequence));
        while (m_tree.back().size() > 1 && !is_terminating_sequence(m_tree.back())) {
            Sequence next_row(m_tree.back().size() - 1);
            for (Size index = 1; index < m_tree.back().size(); index++) {
                next_row[index - 1] = (m_tree.back()[index] - m_tree.back()[index - 1]);
            }
            m_tree.push_back(std::move(next_row));
        }
    }

    int extrapolate() const {
        int next_item = m_tree.back().back();
        for (auto list_iter = rbegin() + 1; list_iter != rend(); list_iter++) {
            auto lower_list = list_iter - 1;
            next_item += list_iter->back();
        }

        return next_item;
    }
};

} // namespace

int AoC::day9_solution_part1(std::string_view input) {
    const auto lines = Utils::String::split(input, '\n');

    int result{};

    for (const auto& line : lines) {
        Sequence seq = Utils::parse_list<int>(line);
        SequenceTree tree{seq};
        result += tree.extrapolate();
    }

    return result;
}

std::size_t AoC::day9_solution_part2(std::string_view input) { return 0; }
