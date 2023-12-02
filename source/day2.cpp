#include "day2.hpp"
#include "utils.hpp"

#include <algorithm>
#include <numeric>
#include <map>
#include <optional>
#include <stdexcept>
#include <vector>

namespace {

enum class Color { Red, Green, Blue };

struct CubeCount {
    int red{0};
    int green{0};
    int blue{0};
};

using GameResult = std::vector<CubeCount>;

int get_game_id(std::string_view line) {
    const auto game_info_string = AoC::split(line, ':')[0];
    const auto id_string = AoC::split(game_info_string, ' ')[1];
    int result{};
    AoC::from_chars_wrapper(id_string, result);
    return result;
}

class ColorParser {

public:
    static constexpr std::string_view::size_type not_found_pos = std::string_view::npos;

    using SizeType = std::string_view::size_type;
    using Iterator = std::string_view::const_iterator;

    GameResult parse_count(std::string_view line) const {
        GameResult game_result{};
        CubeCount result{};
        for (Iterator it = line.begin(); it != line.end();) {
            if (*it == ';') {
                game_result.push_back(result);
                result = CubeCount{};
            }
            if (is_delimiter(*it)) {
                it += 2; // skip space
                // parse number
                auto next_space_it = std::find(it, line.end(), ' ');
                if (next_space_it == line.end()) {
                    throw std::runtime_error("Malformed input string");
                }
                int count{};
                AoC::from_chars_wrapper(std::string_view{it, next_space_it}, count);
                // parse color
                it = next_space_it + 1;
                auto color = parse_color_from_string(it, line.end());
                if (!color) {
                    throw std::runtime_error("Unable to parse color from string");
                }

                switch (*color) {
                case Color::Red:
                    result.red += count;
                    break;
                case Color::Green:
                    result.green += count;
                    break;
                case Color::Blue:
                    result.blue += count;
                    break;
                default:
                    throw std::runtime_error("Invalid color code");
                }
            }
            // increment iterator
            it = get_next_delimiter_or_eol(it, line.end());
        }
        game_result.push_back(result);

        return game_result;
    }

    GameResult parse_max_count(std::string_view line) const {
        GameResult game_result{};
        CubeCount result{};
        for (Iterator it = line.begin(); it != line.end();) {
            if (*it == ';') {
                game_result.push_back(result);
                result = CubeCount{};
            }
            if (is_delimiter(*it)) {
                it += 2; // skip space
                // parse number
                auto next_space_it = std::find(it, line.end(), ' ');
                if (next_space_it == line.end()) {
                    throw std::runtime_error("Malformed input string");
                }
                int count{};
                AoC::from_chars_wrapper(std::string_view{it, next_space_it}, count);
                // parse color
                it = next_space_it + 1;
                auto color = parse_color_from_string(it, line.end());
                if (!color) {
                    throw std::runtime_error("Unable to parse color from string");
                }

                switch (*color) {
                case Color::Red:
                    if (count > result.red) {
                        result.red = count;
                    }
                    break;
                case Color::Green:
                    if (count > result.green) {
                        result.green = count;
                    }
                    break;
                case Color::Blue:
                    if (count > result.blue) {
                        result.blue = count;
                    }
                    break;
                default:
                    throw std::runtime_error("Invalid color code");
                }
            }
            // increment iterator
            it = get_next_delimiter_or_eol(it, line.end());
        }
        game_result.push_back(result);

        return game_result;
    }

private:
    Iterator get_next_delimiter_or_eol(Iterator begin, Iterator end) const {
        return std::find_if(begin, end, [this](const char item) { return is_delimiter(item); });
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

    static bool is_delimiter(char item) { return item == ':' || item == ',' || item == ';'; }

    int parse_color_count(std::string_view line, Color color) {}

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

        auto is_valid = std::all_of(game_result.begin(), game_result.end(), [](const auto count) {
            return count.red <= max_red_cubes && count.green <= max_green_cubes &&
                   count.blue <= max_blue_cubes;
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
        const auto game_result = parser.parse_max_count(line);
        const auto game_id = get_game_id(line);

        auto max_red = std::accumulate(game_result.begin(), game_result.end(), 0, [](int max, const auto result){
            if (result.red > max) {
                return result.red;
            }
            return max;
        });
        auto max_green = std::accumulate(game_result.begin(), game_result.end(), 0, [](int max, const auto result){
            if (result.green > max) {
                return result.green;
            }
            return max;
        });
        auto max_blue = std::accumulate(game_result.begin(), game_result.end(), 0, [](int max, const auto result){
            if (result.blue > max) {
                return result.blue;
            }
            return max;
        });

        sum_of_powers += max_red * max_green * max_blue;
    });

    return sum_of_powers;
}