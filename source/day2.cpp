#include "day2.hpp"
#include "utils.hpp"

#include <algorithm>
#include <map>
#include <numeric>
#include <optional>
#include <stdexcept>
#include <vector>

namespace {

enum class Color { Red, Green, Blue };

struct RoundCount {
    std::vector<int> red{};
    std::vector<int> green{};
    std::vector<int> blue{};
};

using GameResult = std::vector<RoundCount>;

int get_game_id(std::string_view line) {
    const auto game_info_string = AoC::split(line, ':')[0];
    const auto id_string = AoC::split(game_info_string, ' ')[1];
    int result{};
    AoC::from_chars_wrapper(id_string, result);
    return result;
}

class ColorParser {

public:
    using Iterator = std::string_view::const_iterator;

    GameResult parse_count(std::string_view line) const {
        GameResult game_result{};
        RoundCount round_result{};
        for (Iterator it = line.begin(); it != line.end();) {
            if (*it == ';') {
                game_result.push_back(round_result);
                round_result = RoundCount{};
            }
            if (is_delimiter(*it)) {
                it += 2; // skip space
                // parse number
                auto next_space_it = std::find(it, line.end(), ' ');
                if (next_space_it == line.end()) {
                    throw std::runtime_error("Malformed input string");
                }
                int color_quantity{};
                AoC::from_chars_wrapper(std::string_view{it, next_space_it}, color_quantity);
                // parse color
                it = next_space_it + 1;
                auto color = parse_color_from_string(it, line.end());
                if (!color) {
                    throw std::runtime_error("Unable to parse color from string");
                }

                // write color value into round_result
                handle_color(round_result, *color, color_quantity);
            }
            // increment iterator
            it = get_next_delimiter_or_eol(it, line.end());
        }

        // when reaching line.end() last round round_result doesn't get pushed in the for loop
        game_result.push_back(round_result);

        return game_result;
    }

private:
    static Iterator get_next_delimiter_or_eol(Iterator begin, Iterator end) {
        return std::find_if(begin, end, [](const char item) { return is_delimiter(item); });
    }

    std::optional<Color> parse_color_from_string(Iterator begin, Iterator end) const {
        auto next_delimiter_or_eol = get_next_delimiter_or_eol(begin, end);
        // iterator end is fine since each line can end with a color name
        const std::string_view color_str{begin, next_delimiter_or_eol};
        std::optional<Color> result{};
        for (const auto &[color, str] : m_color_map) {
            if (color_str == str) {
                result = color;
            }
        }
        return result;
    }

    static void handle_color(RoundCount &round_count, Color color, int count) {
        switch (color) {
        case Color::Red:
            round_count.red.push_back(count);
            break;
        case Color::Green:
            round_count.green.push_back(count);
            break;
        case Color::Blue:
            round_count.blue.push_back(count);
            break;
        default:
            throw std::runtime_error("Invalid color code");
        }
    }

    static bool is_delimiter(char item) { return item == ':' || item == ',' || item == ';'; }

    std::map<Color, std::string_view> m_color_map{
        {Color::Red, "red"}, {Color::Green, "green"}, {Color::Blue, "blue"}};
};

constexpr int max_red_cubes = 12;
constexpr int max_green_cubes = 13;
constexpr int max_blue_cubes = 14;

} // anonymous namespace

int AoC::day2_solution_part1(std::string_view input) {
    const auto lines = split(input, '\n');
    ColorParser parser{};
    int sum_of_game_ids{};

    std::for_each(lines.begin(), lines.end(), [&parser, &sum_of_game_ids](const auto line) {
        const auto game_result = parser.parse_count(line);
        const auto game_id = get_game_id(line);

        auto is_valid = std::all_of(game_result.begin(), game_result.end(), [](const auto round_count) {
            const auto count_red = std::accumulate(round_count.red.begin(), round_count.red.end(), 0,
                                                   [](int sum, int count) { return sum + count; });
            const auto count_green = std::accumulate(round_count.green.begin(), round_count.green.end(), 0,
                                                     [](int sum, int count) { return sum + count; });
            const auto count_blue = std::accumulate(round_count.blue.begin(), round_count.blue.end(), 0,
                                                    [](int sum, int count) { return sum + count; });
            return count_red <= max_red_cubes && count_green <= max_green_cubes &&
                   count_blue <= max_blue_cubes;
        });

        if (is_valid) {
            sum_of_game_ids += game_id;
        }
    });

    return sum_of_game_ids;
}

int AoC::day2_solution_part2(std::string_view input) {
    const auto lines = split(input, '\n');
    ColorParser parser{};
    int sum_of_powers{};

    std::for_each(lines.begin(), lines.end(), [&parser, &sum_of_powers](const auto line) {
        const auto game_result = parser.parse_count(line);

        auto max_red = std::accumulate(game_result.begin(), game_result.end(), 0,
                                       [](int max_in_game, const auto round_count) {
            const auto max_red = std::accumulate(round_count.red.begin(), round_count.red.end(), 0,
                                                 [](int max_in_round, int count) {
                if (count > max_in_round) {
                    return count;
                }
                return max_in_round;
            });
            if (max_red > max_in_game) {
                return max_red;
            }
            return max_in_game;
        });
        auto max_green = std::accumulate(game_result.begin(), game_result.end(), 0,
                                       [](int max_in_game, const auto round_count) {
            const auto max_green = std::accumulate(round_count.green.begin(), round_count.green.end(), 0,
                                                 [](int max_in_round, int count) {
                if (count > max_in_round) {
                    return count;
                }
                return max_in_round;
            });
            if (max_green > max_in_game) {
                return max_green;
            }
            return max_in_game;
        });
        auto max_blue = std::accumulate(game_result.begin(), game_result.end(), 0,
                                       [](int max_in_game, const auto round_count) {
            const auto max_blue = std::accumulate(round_count.blue.begin(), round_count.blue.end(), 0,
                                                 [](int max_in_round, int count) {
                if (count > max_in_round) {
                    return count;
                }
                return max_in_round;
            });
            if (max_blue > max_in_game) {
                return max_blue;
            }
            return max_in_game;
        });

        sum_of_powers += max_red * max_green * max_blue;
    });

    return sum_of_powers;
}