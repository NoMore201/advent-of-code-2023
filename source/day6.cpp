#include "day6.hpp"
#include "string.hpp"
#include "utils.hpp"

#include <gsl/assert>

namespace {

using usize = std::size_t; // NOLINT(readability-identifier-naming)

constexpr usize speed_increase_per_ms_factor = 1; // each ms holding button, speed increases by x*factor mm/ms

usize parse_full_integer(std::string_view line) {
    std::string line_without_spaces{};

    std::copy_if(line.begin(), line.end(), std::back_inserter(line_without_spaces),
                 [](char item) { return item != ' '; });
    const auto line_split_by_colon = Utils::String::split(line_without_spaces, ':');
    return Utils::parse_integer<usize>(line_split_by_colon[1]);
}

} // anonymous namespace

std::size_t AoC::day6_solution_part1(std::string_view input) {
    const auto lines = Utils::String::split(input, '\n');
    const auto times = Utils::parse_list<usize>(lines[0]);
    const auto distances = Utils::parse_list<usize>(lines[1]);

    Ensures(times.size() == distances.size());

    usize result{1};
    for (usize race = 0; race < times.size(); race++) {
        auto record = distances[race];
        auto race_duration = times[race];
        usize ways_we_could_win = 0;

        for (usize hold_time = 0; hold_time <= race_duration; hold_time++) {
            const auto speed = hold_time * speed_increase_per_ms_factor;
            const auto time_left_for_running = race_duration - hold_time;
            const auto distance_travelled = time_left_for_running * speed;
            if (distance_travelled > record) {
                ways_we_could_win++;
            }
        }

        result *= ways_we_could_win;
    }

    return result;
}

std::size_t AoC::day6_solution_part2(std::string_view input) {
    const auto lines = Utils::String::split(input, '\n');
    auto race_duration = parse_full_integer(lines[0]);
    auto record = parse_full_integer(lines[1]);

    usize ways_we_could_win = 0;

    for (usize hold_time = 0; hold_time <= race_duration; hold_time++) {
        const auto speed = hold_time * speed_increase_per_ms_factor;
        const auto time_left_for_running = race_duration - hold_time;
        const auto distance_travelled = time_left_for_running * speed;
        if (distance_travelled > record) {
            ways_we_could_win++;
        }
    }

    return ways_we_could_win;
}
