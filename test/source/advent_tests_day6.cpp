#include <gtest/gtest.h>

#include <day6.hpp>

#include <string_view>

namespace {

constexpr std::string_view exercise_input{
    "Time:        41     96     88     94\n"
    "Distance:   214   1789   1127   1055"
};

constexpr std::string_view example_input{
    "Time:      7  15   30\n"
    "Distance:  9  40  200"
};

} // anonymous namespace

TEST(AdventOfCode, Day6Part1) {
    EXPECT_EQ(4811940, AoC::day6_solution_part1(exercise_input));
}

TEST(AdventOfCode, Day6Part2) {
    EXPECT_EQ(30077773, AoC::day6_solution_part2(exercise_input));
}