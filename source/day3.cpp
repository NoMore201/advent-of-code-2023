#include "day3.hpp"
#include "gsl/assert"
#include "utils.hpp"

#include <cctype>
#include <charconv>
#include <string_view>
#include <vector>

namespace {

using Matrix = std::vector<std::string>;

struct NumberFinding {
    std::ptrdiff_t begin{};
    std::ptrdiff_t end{};
};

std::vector<NumberFinding> find_numbers_in_string(const std::string &input) {
    const auto begin_it = input.begin();
    const auto end_it = input.end();
    const auto *begin_ptr = &*begin_it;
    const auto *end_ptr = begin_ptr + static_cast<std::ptrdiff_t>(input.size());
    std::vector<NumberFinding> result{};
    for (auto it = begin_it; it != end_it;) {
        std::size_t parsed_value{};
        auto parse_result = std::from_chars(&*it, end_ptr, parsed_value);
        if (parse_result.ec == std::errc()) {
            // found a number
            auto number_length = parse_result.ptr - &*it;
            auto begin_index = std::distance(begin_it, it);
            auto end_index = begin_index + (parse_result.ptr - &*it);
            result.push_back(NumberFinding{begin_index, end_index});
            it += number_length;
        } else {
            it++;
        }
    }
    return result;
}

bool is_symbol(char item) { return item != '.' && std::ispunct(item) != 0; }

Matrix create_matrix(std::string_view input) {
    Matrix matrix{};
    const auto lines = Utils::split(input, '\n');
    for (const auto &line : lines) {
        matrix.emplace_back(line.begin(), line.end());
    }
    return matrix;
}

bool does_range_contain_symbol(const std::string &row, NumberFinding range) {
    for (auto index = range.begin; index < range.end; index++) {
        if (is_symbol(row[index])) {
            return true;
        }
    }
    return false;
}

bool is_part_number(const Matrix &matrix, std::size_t row, NumberFinding number_columns) {
    // check same row, item to the left and right
    const auto row_size = matrix[0].size();
    if (number_columns.begin > 0 && is_symbol(matrix[row][number_columns.begin - 1]) ||
        number_columns.end < row_size && is_symbol(matrix[row][number_columns.end])) {
        return true;
    }
    // check row before (if any)
    auto begin_index = number_columns.begin;
    if (begin_index > 0) {
        // also diagonal needs to be checked
        begin_index--;
    }
    auto end_index = number_columns.end;
    if (end_index < row_size) {
        end_index++;
    }
    if (row > 0) {
        if (does_range_contain_symbol(matrix[row - 1], NumberFinding{begin_index, end_index})) {
            return true;
        }
    }
    if ((row + 1) < matrix.size()) {
        if (does_range_contain_symbol(matrix[row + 1], NumberFinding{begin_index, end_index})) {
            return true;
        }
    }

    return false;
}

std::vector<std::size_t> find_adjacent_numbers(const Matrix &matrix, std::size_t row, std::size_t column) {
    if (row >= matrix.size() || column >= matrix[0].size()) {
        throw std::runtime_error("Invalid coordinates");
    }

    std::vector<std::size_t> result{};

    auto findings = find_numbers_in_string(matrix[row]);
    for (auto range : findings) {
        if (range.end == column || range.begin == (column + 1)) {
            const auto gear_ratio = Utils::parse_integer<std::size_t>(matrix[row].begin() + range.begin,
                                                                    matrix[row].begin() + range.end);
            result.push_back(gear_ratio);
        }
    }
    if (row > 0) {
        const auto &str_ref = matrix[row - 1];
        findings = find_numbers_in_string(str_ref);
        for (auto range : findings) {
            if (range.end == column || range.begin == (column + 1) ||
                (column >= range.begin && column <= range.end)) {
                const auto gear_ratio = Utils::parse_integer<std::size_t>(str_ref.begin() + range.begin,
                                                                        str_ref.begin() + range.end);
                result.push_back(gear_ratio);
            }
        }
    }
    if (row + 1 < matrix.size()) {
        const auto &str_ref = matrix[row + 1];
        findings = find_numbers_in_string(str_ref);
        for (auto range : findings) {
            if (range.end == column || range.begin == (column + 1) ||
                (column >= range.begin && column <= range.end)) {
                const auto gear_ratio = Utils::parse_integer<std::size_t>(str_ref.begin() + range.begin,
                                                                        str_ref.begin() + range.end);
                result.push_back(gear_ratio);
            }
        }
    }

    return result;
}

} // anonymous namespace

int AoC::day3_solution_part1(std::string_view input) {
    auto matrix = create_matrix(input);

    int sum = 0;

    for (std::size_t row_index = 0; row_index < matrix.size(); row_index++) {
        auto findings = find_numbers_in_string(matrix[row_index]);
        for (auto range : findings) {
            if (is_part_number(matrix, row_index, range)) {
                const auto &row_str = matrix[row_index];
                sum += Utils::parse_integer<int>(row_str.begin() + range.begin, row_str.begin() + range.end);
            }
        }
    }

    return sum;
}

std::size_t AoC::day3_solution_part2(std::string_view input) {
    auto matrix = create_matrix(input);

    std::size_t sum = 0;

    for (std::size_t row_index = 0; row_index < matrix.size(); row_index++) {
        for (std::size_t column_index = 0; column_index < matrix[row_index].size(); column_index++) {
            if (matrix[row_index][column_index] == '*') {
                auto adjacent_gear_ratios = find_adjacent_numbers(matrix, row_index, column_index);
                if (adjacent_gear_ratios.size() == 2) {
                    sum += adjacent_gear_ratios[0] * adjacent_gear_ratios[1];
                }
            }
        }
    }

    return sum;
}