#include "day1.hpp"
#include "utils.hpp"

#include <gsl/assert>

#include <algorithm>
#include <cctype>
#include <numeric>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

namespace {

bool is_numeric(char item) { return std::isdigit(item) != 0; }

int parse_number_from_digits(std::string_view line) {
    const auto first_number_it = std::find_if(line.begin(), line.end(), is_numeric);
    const auto last_number_it = std::find_if(line.rbegin(), line.rend(), is_numeric);
    Ensures(first_number_it != line.end() && last_number_it != line.rend());

    std::string final_number{};
    final_number.push_back(*first_number_it);
    final_number.push_back(*last_number_it);

    int result{};
    AoC::from_chars_wrapper(final_number, result);
    return result;
}

const std::unordered_map<std::string_view, int> word_map{
    {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
    {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9},
};

const std::unordered_map<char, int> digit_map{
    {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9},
};

constexpr auto not_found_index = std::string_view::npos;

std::optional<int> get_first_match(std::string_view line) {
    auto left_most_index{not_found_index};
    auto result{0};
    for (const auto& [str, value] : word_map) {
        const auto index = line.find(str);
        if (index != not_found_index && index < left_most_index) {
            left_most_index = index;
            result = value;
        }
    }
    for (const auto& [character, value] : digit_map) {
        const auto index = line.find(character);
        if (index != not_found_index && index < left_most_index) {
            left_most_index = index;
            result = value;
        }
    }

    if (left_most_index == not_found_index) {
        return {};
    }
    return {result};
}

std::optional<int> get_last_match(std::string_view line) {
    auto right_most_index{0ULL};
    auto result{0};
    bool found_at_least_one{false};
    for (const auto& [str, value] : word_map) {
        const auto index = line.rfind(str);
        if (index != not_found_index && index >= right_most_index) {
            found_at_least_one = true;
            right_most_index = index;
            result = value;
        }
    }
    for (const auto& [character, value] : digit_map) {
        const auto index = line.rfind(character);
        if (index != not_found_index && index >= right_most_index) {
            found_at_least_one = true;
            right_most_index = index;
            result = value;
        }
    }

    if (!found_at_least_one) {
        return {};
    }

    return {result};
}

int parse_number_from_words(std::string_view line) {
    int result{0};

    auto first_match = get_first_match(line);
    auto last_match = get_last_match(line);

    Ensures(first_match.has_value() && last_match.has_value());
    result += *first_match * 10;
    result += *last_match;

    return result;
}

} // anonymous namespace

int AoC::day1_solution_part1(std::string_view input) {
    const auto lines = split(input, '\n');

    return std::accumulate(lines.begin(), lines.end(), 0, [](int sum, std::string_view line) {
        return sum + parse_number_from_digits(line);
    });
}

int AoC::day1_solution_part2(std::string_view input) {
    const auto lines = split(input, '\n');

    return std::accumulate(lines.begin(), lines.end(), 0, [](int sum, std::string_view line) {
        return sum + parse_number_from_words(line);
    });
}