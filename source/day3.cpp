#include "day3.hpp"
#include "string.hpp"
#include "utils.hpp"

#include <cctype>
#include <cstdint>
#include <numeric>
#include <string_view>
#include <variant>
#include <vector>

namespace {

bool is_symbol(char item) { return item != '.' && std::ispunct(item) != 0; }

bool is_digit(char item) { return std::isdigit(item) != 0; }

struct Range {
    std::size_t begin;
    std::size_t end;
};

struct Object {

    enum class Type : std::uint8_t { Number, Symbol };

    Type type;
    std::variant<std::size_t, char> content;
    std::size_t row;
    Range column_range;

    bool is_within_range_of(const Object &other) const {
        Range vertical_range{row, row + 1};
        if (vertical_range.begin > 0) {
            vertical_range.begin -= 1;
        }
        Range horizontal_range{column_range.begin, column_range.end + 1};
        if (horizontal_range.begin > 0) {
            horizontal_range.begin -= 1;
        }
        if (other.row >= vertical_range.begin && other.row <= vertical_range.end) {
            if (other.column_range.begin >= horizontal_range.begin &&
                other.column_range.end <= horizontal_range.end) {
                return true;
            }
        }
        return false;
    }
};

std::vector<Object> parse_objects(std::string_view line) {
    std::vector<Object> result{};
    const auto lines = Utils::String::split(line, '\n');

    for (std::size_t row = 0; row < lines.size(); row++) {
        const auto line_size = lines[row].size();
        for (std::size_t column = 0; column < line_size;) {
            const char item = lines[row][column];
            if (is_symbol(item)) {
                const Object obj{Object::Type::Symbol, item, row, Range{column, column}};
                result.push_back(obj);
                column++;
            } else if (is_digit(item)) {
                auto substr = lines[row].substr(column);
                auto parse_result = Utils::try_parse_number<std::size_t>(substr);
                if (parse_result) {
                    auto offset = static_cast<size_t>(parse_result->iterator_offset);
                    const Object obj{Object::Type::Number, parse_result->final_number, row,
                                     Range{column, column + offset - 1}};
                    result.push_back(obj);
                    column += offset;
                } else {
                    column++;
                }
            } else {
                column++;
            }
        }
    }

    return result;
}

} // anonymous namespace

std::size_t AoC::day3_solution_part1(std::string_view input) {
    std::size_t sum{};
    const auto findings = parse_objects(input);

    for (const auto &current_object : findings) {
        if (current_object.type == Object::Type::Number) {
            auto iter = std::find_if(findings.begin(), findings.end(), [&current_object](const Object &obj) {
                if (obj.type == Object::Type::Symbol) {
                    return current_object.is_within_range_of(obj);
                }
                return false;
            });

            if (iter != findings.end()) {
                sum += std::get<std::size_t>(current_object.content);
            }
        }
    }
    return sum;
}

std::size_t AoC::day3_solution_part2(std::string_view input) {
    const auto findings = parse_objects(input);

    std::size_t sum{};
    for (const Object &object : findings) {
        if (object.type == Object::Type::Symbol && std::get<char>(object.content) == '*') {
            std::vector<Object> surrounding_numbers{};
            std::copy_if(findings.begin(), findings.end(), std::back_inserter(surrounding_numbers),
                         [&object](const Object &inner) {
                return (inner.type == Object::Type::Number && inner.is_within_range_of(object));
            });

            if (surrounding_numbers.size() == 2) {
                sum += std::get<std::size_t>(surrounding_numbers[0].content) *
                       std::get<std::size_t>(surrounding_numbers[1].content);
            }
        }
    }
    return sum;
}