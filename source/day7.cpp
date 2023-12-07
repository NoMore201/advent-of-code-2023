#include "day7.hpp"
#include "utils.hpp"

#include <gsl/assert>

#include <array>
#include <bitset>
#include <cstdint>
#include <numeric>
#include <string_view>
#include <vector>

namespace {

using usize = std::size_t;

enum class HandType : uint8_t {
    HighCard = 1,
    OnePair = 2,
    TwoPair = 3,
    ThreeOfAKind = 4,
    FullHouse = 5,
    FourOfAKind = 6,
    FiveOfAKind = 7
};

using DiffPoint = unsigned char;
constexpr DiffPoint max_diff_point_value{15};

int map_card_to_rank(char item) {
    switch (item) {
    case 'A':
        return 13;
    case 'K':
        return 12;
    case 'Q':
        return 11;
    case 'J':
        return 10;
    case 'T':
        return 9;
    case '9':
        return 8;
    case '8':
        return 7;
    case '7':
        return 6;
    case '6':
        return 5;
    case '5':
        return 4;
    case '4':
        return 3;
    case '3':
        return 2;
    case '2':
        return 1;
    default:
        throw std::runtime_error("Wrong card value");
    }
}

int map_card_to_rank_step_two(char item) {
    switch (item) {
    case 'A':
        return 13;
    case 'K':
        return 12;
    case 'Q':
        return 11;
    case 'T':
        return 10;
    case '9':
        return 9;
    case '8':
        return 8;
    case '7':
        return 7;
    case '6':
        return 6;
    case '5':
        return 5;
    case '4':
        return 4;
    case '3':
        return 3;
    case '2':
        return 2;
    case 'J':
        return 1;
    default:
        throw std::runtime_error("Wrong card value");
    }
}

constexpr HandType map_diff_point_to_type(DiffPoint diff_point) {
    Expects(diff_point <= max_diff_point_value);

    constexpr std::array<HandType, max_diff_point_value + 1> map{
        HandType::FiveOfAKind,  // 0 0b0000
        HandType::FourOfAKind,  // 1 0b0001
        HandType::FullHouse,    // 2 0b0010
        HandType::ThreeOfAKind, // 3 0b0011
        HandType::FullHouse,    // 4 0b0100
        HandType::TwoPair,      // 5 0b0101
        HandType::TwoPair,      // 6 0b0110
        HandType::OnePair,      // 7 0b0111
        HandType::FourOfAKind,  // 8 0b1000
        HandType::ThreeOfAKind, // 9 0b1001
        HandType::TwoPair,      // 10 0b1010
        HandType::OnePair,      // 11 0Bb1011
        HandType::ThreeOfAKind, // 12 0b1100
        HandType::OnePair,      // 13 0b1101
        HandType::OnePair,      // 14 0b1110
        HandType::HighCard,     // 15 0b1111

    };

    return map.at(diff_point);
}

struct CardsCombination {
    static constexpr usize max_size = 5;

    using ContainerType = std::array<char, max_size>;

    ContainerType sorted;
    ContainerType original;
    std::vector<char> sorted_jokers;
    usize number_of_jokers;
    usize bid;

    explicit CardsCombination(std::string_view line) {
        const auto line_segments = Utils::split(line, ' ');
        Ensures(line_segments.size() == 2 && line_segments[0].size() == 5);
        std::copy(line_segments[0].begin(), line_segments[0].end(), original.begin());
        std::copy(original.begin(), original.end(), sorted.begin());
        std::sort(sorted.begin(), sorted.end());
        std::copy_if(sorted.begin(), sorted.end(), std::back_inserter(sorted_jokers),
                     [](char item) { return item != 'J'; });
        number_of_jokers = static_cast<usize>(std::count(original.begin(), original.end(), 'J'));
        // idea: we consider joker as the highest rank card in the pool
        for (usize index = 0; index < number_of_jokers; index++) {
            auto highest_rank_card = sorted[0];
            sorted_jokers.insert(sorted_jokers.begin(), highest_rank_card);
        }
        bid = Utils::parse_integer<usize>(line_segments[1]);
    }

    static DiffPoint get_diff_points(const auto& container) {
        std::bitset<max_size - 1> bitset{};
        char last_item = container[0];
        for (usize index = 1; index < container.size(); index++) {
            if (container.at(index) != last_item) {
                bitset.set(index - 1);
            }
            last_item = container.at(index);
        }
        return static_cast<DiffPoint>(bitset.to_ulong());
    }

    HandType get_hand_type() const { return map_diff_point_to_type(get_diff_points(sorted)); }
    HandType get_hand_type_with_jokers() const { return map_diff_point_to_type(get_diff_points(sorted_jokers)); }

};

std::vector<CardsCombination> parse_card_hands_list(const std::vector<std::string_view> &lines) {
    std::vector<CardsCombination> result{};

    std::transform(lines.begin(), lines.end(), std::back_inserter(result),
                   [](std::string_view line) { return CardsCombination{line}; });

    return result;
}

void sort_hands_by_rank(std::vector<CardsCombination> &hands) {
    std::sort(hands.begin(), hands.end(), [](const CardsCombination &first, const CardsCombination &second) {
        // returns true if the first argument is less than (i.e. is ordered before) the second.
        auto first_type = first.get_hand_type();
        auto second_type = second.get_hand_type();
        if (first_type != second_type) {
            return static_cast<int>(first_type) < static_cast<int>(second_type);
        }

        for (usize index = 0; index < CardsCombination::max_size; index++) {
            auto first_card_rank = map_card_to_rank(first.original.at(index));
            auto second_card_rank = map_card_to_rank(second.original.at(index));
            if (first_card_rank == second_card_rank) {
                continue;
            }
            return first_card_rank < second_card_rank;
        }
    });
}

void sort_hands_by_rank_with_joker(std::vector<CardsCombination> &hands) {
    std::sort(hands.begin(), hands.end(), [](const CardsCombination &first, const CardsCombination &second) {
        // returns true if the first argument is less than (i.e. is ordered before) the second.
        auto first_type = first.get_hand_type_with_jokers();
        auto second_type = second.get_hand_type_with_jokers();
        if (first_type != second_type) {
            return static_cast<int>(first_type) < static_cast<int>(second_type);
        }

        for (usize index = 0; index < CardsCombination::max_size; index++) {
            auto first_card_rank = map_card_to_rank_step_two(first.original.at(index));
            auto second_card_rank = map_card_to_rank_step_two(second.original.at(index));
            if (first_card_rank == second_card_rank) {
                continue;
            }
            return first_card_rank < second_card_rank;
        }
    });
}

} // namespace

std::size_t AoC::day7_solution_part1(std::string_view input) {
    const auto lines = Utils::split(input, '\n');
    auto hands = parse_card_hands_list(lines);
    sort_hands_by_rank(hands);

    usize total_winnings{};
    usize current_rank{1};

    for (const auto &hand : hands) {
        total_winnings += current_rank * hand.bid;
        current_rank++;
    }

    return total_winnings;
}

std::size_t AoC::day7_solution_part2(std::string_view input) {
    const auto lines = Utils::split(input, '\n');
    auto hands = parse_card_hands_list(lines);
    sort_hands_by_rank_with_joker(hands);

    usize total_winnings{};
    usize current_rank{1};

    for (const auto &hand : hands) {
        total_winnings += current_rank * hand.bid;
        current_rank++;
    }

    return total_winnings;
}
