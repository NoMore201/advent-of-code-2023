#include "day4.hpp"
#include "utils.hpp"

#include <numeric>
#include <string_view>
#include <vector>

namespace {

constexpr int calculate_points(std::size_t number_of_guess) {
    if (number_of_guess == 0) {
        return 0;
    }
    if (number_of_guess == 1) {
        return 1;
    }
    int result = 1;
    for (std::size_t index = 1; index < number_of_guess; index++) {
        result *= 2;
    }
    return result;
}

struct ScratchCard {
    std::vector<int> winning;
    std::vector<int> played;
};

ScratchCard parse_scratch_card(std::string_view line) {
    ScratchCard card;
    const auto number_substring = Utils::split(line, ':');
    const auto sections = Utils::split(number_substring[1], '|');
    const auto &winning_str = sections[0];
    const auto &played_str = sections[1];

    // parse winning numbers
    for (auto it = winning_str.begin(); it != winning_str.end();) {
        auto parse_result = Utils::try_parse_number<int>(it, winning_str.end());
        if (parse_result) {
            card.winning.push_back(parse_result->final_number);
            it += parse_result->iterator_offset;
        } else {
            it++;
        }
    }
    // parse played numbers
    for (auto it = played_str.begin(); it != played_str.end();) {
        auto parse_result = Utils::try_parse_number<int>(it, played_str.end());
        if (parse_result) {
            card.played.push_back(parse_result->final_number);
            it += parse_result->iterator_offset;
        } else {
            it++;
        }
    }

    return card;
}

int get_total_winning_points(const ScratchCard& card)  {
    auto winning_numbers = Utils::find_common_items<int>(card.winning, card.played);

    return calculate_points(winning_numbers.size());
}

} // anonymous namespace

int AoC::day4_solution_part1(std::string_view input) {
    const auto lines = Utils::split(input, '\n');

    return std::accumulate(lines.begin(), lines.end(), 0, [](int sum, std::string_view line) {
        const auto card = parse_scratch_card(line);
        return sum + get_total_winning_points(card);
    });
}

int AoC::day4_solution_part2(std::string_view input) {
    (void)input;
    return 0;
}