#include "day5.hpp"
#include "utils.hpp"

#include <algorithm>
#include <gsl/assert>
#include <map>
#include <numeric>
#include <vector>

namespace {

using usize = std::size_t; // NOLINT(readability-identifier-naming)
using i64 = int64_t; // NOLINT(readability-identifier-naming)

struct Range {
    usize start{};
    usize length{};
    i64 diff{};

    constexpr bool in_range(usize seed) const noexcept {
        return seed >= start && seed < start + length;
    }
};

class SeedMap {
    std::vector<Range> m_map;

public:
    explicit SeedMap(const std::vector<std::string_view> &lines) {
        Expects(lines.size() > 2);
        for (usize index = 1; index < lines.size(); index++) {
            std::vector<usize> numbers{};
            const auto strings = Utils::split(lines[index], ' ');
            std::transform(strings.begin(), strings.end(), std::back_inserter(numbers),
                           [](std::string_view str) { return Utils::parse_integer<usize>(str); });
            Ensures(numbers.size() == 3);
            const auto diff = static_cast<i64>(numbers[0] - numbers[1]);
            m_map.emplace_back(Range{numbers[1], numbers[2], diff});
        }
    }

    usize mapped_value(usize key) const {
        // we assume range do not overlap
        for (const auto& map_range : m_map) {
            if (map_range.in_range(key))
            {
                const auto index = key - map_range.start;
                return map_range.start + index + map_range.diff;
            }
        }

        return key;
    }

    usize get_key_for_value(usize value) const {
        for (const auto& range : m_map) {
            usize start_key = range.start;
            usize final_key = start_key + range.length;
            usize start_value = start_key + range.diff;
            usize final_value = start_value + range.length;
            if (value >= start_value && value < final_value) {
                auto offset = value - start_value;
                return start_key + offset;
            }
        }
        return value;
    }

};

std::vector<usize> parse_seeds(std::string_view line) {
    std::vector<usize> seeds_values;
    auto seed_numbers_strings = Utils::split(line, ' ');
    // erase first element, which is the string "seeds:"
    seed_numbers_strings.erase(seed_numbers_strings.begin());
    std::transform(seed_numbers_strings.begin(), seed_numbers_strings.end(), std::back_inserter(seeds_values),
                   [](std::string_view view) { return Utils::parse_integer<usize>(view); });
    return seeds_values;
}

std::vector<SeedMap> parse_seed_map(const std::vector<std::string_view>& lines) {
    std::vector<SeedMap> seed_map_list{};

    for (auto current_it = lines.begin() + 2; current_it != lines.end();) {
        auto next_empty_line_it =
            std::find_if(current_it, lines.end(), [](std::string_view str) { return str.empty(); });
        std::vector<std::string_view> sub_list{};
        std::copy(current_it, next_empty_line_it, std::back_inserter(sub_list));
        seed_map_list.emplace_back(sub_list);
        if (next_empty_line_it != lines.end()) {
            current_it = next_empty_line_it + 1;
        } else {
            current_it = next_empty_line_it;
        }
    }

    return seed_map_list;
}

} // anonymous namespace

std::size_t AoC::day5_solution_part1(std::string_view input) {
    const auto lines = Utils::split(input, '\n');
    std::vector<SeedMap> seed_map_list = parse_seed_map(lines);
    const std::vector<usize> seeds = parse_seeds(lines[0]);

    std::vector<usize> result;
    for (const auto seed : seeds) {
        usize transformed = seed;
        for (const auto& map : seed_map_list) {
            transformed = map.mapped_value(transformed);
        }
        result.push_back(transformed);
    }

    return *std::min_element(result.begin(), result.end());
}

std::size_t AoC::day5_solution_part2(std::string_view input) {
    const auto lines = Utils::split(input, '\n');
    std::vector<SeedMap> seed_map_list = parse_seed_map(lines);
    std::vector<usize> seeds = parse_seeds(lines[0]);

    // build final seed list from ranges
    std::vector<Range> final_seed_list;
    for (std::size_t index = 0; index < seeds.size(); index += 2) {
        final_seed_list.emplace_back(seeds[index], seeds[index + 1], 0);
    }

    // idea: do a reverse map -> iterate from the smallest final value and go
    // backward finding the original key that generated it. Then check if that
    // key is contained in original list
    auto humidity_to_location = seed_map_list.back();
    auto max_seed_range = std::max_element(final_seed_list.begin(), final_seed_list.end(), [](const Range& first, const Range& second){
       return first.start + first.length < second.start + second.length;
    });
    Ensures(max_seed_range != final_seed_list.end());
    usize max_seed_value = max_seed_range->start + max_seed_range->length;

    for (usize location_value = 0; location_value < max_seed_value; location_value++) {
        auto current_value = location_value;
        usize final_key = 0;
        for (auto iter = seed_map_list.rbegin(); iter != seed_map_list.rend(); iter++) {
            final_key = iter->get_key_for_value(current_value);
            // in the previous map, the current key becomes the location_value
            current_value = final_key;
        }

        auto is_in_original_range = std::any_of(final_seed_list.begin(), final_seed_list.end(), [final_key](const Range& range){
            return range.in_range(final_key);
        });
        if (is_in_original_range) {
            return location_value;
        }
    }

    throw std::runtime_error("Value not found");
}
