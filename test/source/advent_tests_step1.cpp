#include <gtest/gtest.h>

#include <step1.hpp>

namespace {

constexpr std::string_view exercise_input{};

} // anonymous namespace

TEST(AdventOfCode, Step1Part1) {
  EXPECT_EQ(68787, AdventOfCode::step1_solution_part1(exercise_input));
}

TEST(AdventOfCode, Step1Part2) {
  EXPECT_EQ(198041, AdventOfCode::step1_solution_part2(exercise_input));
}