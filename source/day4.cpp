#include "day4.hpp"
#include "utils.hpp"

#include <map>
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
    std::vector<int> winning{};
    std::vector<int> played{};
    std::size_t copies{1};
};

std::size_t parse_card_number(std::string_view line) {
    const auto sections = Utils::split(line, ':');
    const auto split_card_label = Utils::split(sections[0], ' ');

    // there may be multiple spaces between "Card" label and the number
    return Utils::parse_integer<std::size_t>(split_card_label.back());
}

ScratchCard parse_scratch_card(std::string_view line) {
    ScratchCard card;
    const auto number_substring = Utils::split(line, ':');
    const auto sections = Utils::split(number_substring[1], '|');
    const auto &winning_str = sections[0];
    const auto &played_str = sections[1];

    // parse winning numbers
    for (std::size_t index = 0; index < winning_str.size(); ) {
        auto parse_result = Utils::try_parse_number<int>(winning_str.substr(index));
        if (parse_result) {
            card.winning.push_back(parse_result->final_number);
            index += static_cast<std::size_t>(parse_result->iterator_offset);
        } else {
            index++;
        }
    }
    // parse played numbers
    for (std::size_t index = 0; index < played_str.size(); ) {
        auto parse_result = Utils::try_parse_number<int>(played_str.substr(index));
        if (parse_result) {
            card.played.push_back(parse_result->final_number);
            index += static_cast<size_t>(parse_result->iterator_offset);
        } else {
            index++;
        }
    }

    return card;
}

std::size_t get_number_of_winning_entries(const ScratchCard &card) {
    return Utils::find_common_items<int>(card.winning, card.played).size();
}

int get_total_winning_points(const ScratchCard &card) {
    return calculate_points(get_number_of_winning_entries(card));
}

} // anonymous namespace

int AoC::day4_solution_part1(std::string_view input) {
    const auto lines = Utils::split(input, '\n');

    return std::accumulate(lines.begin(), lines.end(), 0, [](int sum, std::string_view line) {
        const auto card = parse_scratch_card(line);
        return sum + get_total_winning_points(card);
    });
}

std::size_t AoC::day4_solution_part2(std::string_view input) {
    const auto lines = Utils::split(input, '\n');
    std::map<std::size_t, ScratchCard> card_map{};

    for (auto line : lines) {
        auto card = parse_scratch_card(line);
        const auto number = parse_card_number(line);
        card_map.emplace(number, std::move(card));
    };

    for (const auto &pair : card_map) {
        const auto number = pair.first;
        const auto &card = pair.second;
        const auto winning_entries = get_number_of_winning_entries(card);
        for (std::size_t current_entry = number + 1; current_entry < number + 1 + winning_entries;
             current_entry++) {
            card_map.at(current_entry).copies += card.copies;
        }
    };

    return std::accumulate(card_map.begin(), card_map.end(), std::size_t{},
                           [](std::size_t sum, const auto &pair) { return sum + pair.second.copies; });
}