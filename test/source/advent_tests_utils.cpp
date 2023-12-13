#include <gtest/gtest.h>

#include <string.hpp>
#include <utils.hpp>

#include <array>
#include <numeric>
#include <vector>

TEST(Utils, FindCommonItems) {

    constexpr std::string_view first{"abcde"};
    constexpr std::string_view second{"abcgh"};
    auto common_items = Utils::find_common_items<char>(first, second);
    EXPECT_EQ(common_items.size(), 3);
    EXPECT_TRUE(common_items.contains('a'));
    EXPECT_TRUE(common_items.contains('b'));
    EXPECT_TRUE(common_items.contains('c'));

    constexpr std::array<int, 4> dates_first{1992, 2000, 2004, 2023};
    std::vector<int> dates_second(12);
    std::iota(dates_second.begin(), dates_second.end(), 1990);

    auto common_dates = Utils::find_common_items<int>(dates_first, dates_second);
    EXPECT_EQ(common_dates.size(), 2);
    EXPECT_TRUE(common_dates.contains(1992));
    EXPECT_TRUE(common_dates.contains(2000));
    EXPECT_FALSE(common_dates.contains(1991));
    EXPECT_FALSE(common_dates.contains(2023));
}

TEST(Utils, ParseInteger) {
    constexpr std::string_view input_int{" 4096"};
    int const parsed_number = Utils::parse_integer<int>(input_int);
    EXPECT_EQ(parsed_number, 4096);
    std::string const invalid_input{"fake12mixed34"};
    EXPECT_ANY_THROW(Utils::parse_integer<int>(invalid_input));
}