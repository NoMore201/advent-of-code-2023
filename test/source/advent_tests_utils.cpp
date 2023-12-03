#include <gtest/gtest.h>

#include <utils.hpp>

#include <array>
#include <numeric>
#include <vector>

namespace {} // anonymous namespace

TEST(Utils, FindCommonItems) {
    using Utils::find_common_items;
    using Utils::range_to_set;

    constexpr std::string_view first{"abcde"};
    constexpr std::string_view second{"abcgh"};
    auto common_items_range = find_common_items(first, second);
    auto common_items = range_to_set<char>(common_items_range);
    EXPECT_EQ(common_items.size(), 3);
    EXPECT_TRUE(common_items.contains('a'));
    EXPECT_TRUE(common_items.contains('b'));
    EXPECT_TRUE(common_items.contains('c'));

    constexpr std::array<int, 4> dates_first{1992, 2000, 2004, 2023};
    std::vector<int> dates_second(12);
    std::iota(dates_second.begin(), dates_second.end(), 1990);

    auto common_dates_range = find_common_items(dates_first, dates_second);
    auto common_dates = range_to_set<int>(common_dates_range);
    EXPECT_EQ(common_dates.size(), 2);
    EXPECT_TRUE(common_dates.contains(1992));
    EXPECT_TRUE(common_dates.contains(2000));
    EXPECT_FALSE(common_dates.contains(1991));
    EXPECT_FALSE(common_dates.contains(2023));
}

TEST(Utils, StringSplit) {
    constexpr std::string_view input{"c++11,c++14,c++17,c++20,"};

    const auto split_by_comma = Utils::split(input, ',');

    EXPECT_EQ(split_by_comma.size(), 5);
    EXPECT_EQ(split_by_comma[0], "c++11");
    EXPECT_EQ(split_by_comma[1], "c++14");
    EXPECT_EQ(split_by_comma[2], "c++17");
    EXPECT_EQ(split_by_comma[3], "c++20");
    EXPECT_EQ(split_by_comma[4], std::string_view{});
}

TEST(Utils, ParseInteger) {
    constexpr std::string_view input_int{"4096"};
    int parsed_number = Utils::parse_integer<int>(input_int);
    EXPECT_EQ(parsed_number, 4096);
    parsed_number = Utils::parse_integer<int>(input_int.begin(), input_int.end());
    EXPECT_EQ(parsed_number, 4096);
    constexpr std::string_view invalid_input{"fake12mixed34"};
    EXPECT_ANY_THROW(Utils::parse_integer<int>(invalid_input));
}