#include <gtest/gtest.h>

#include <string.hpp>

#include <array>
#include <vector>



TEST(Utils, StringSplit) {
    constexpr std::string_view input{"c++11,c++14,c++17,c++20,"};

    const auto split_by_comma = Utils::String::split(input, ',');

    EXPECT_EQ(split_by_comma.size(), 5);
    EXPECT_EQ(split_by_comma[0], "c++11");
    EXPECT_EQ(split_by_comma[1], "c++14");
    EXPECT_EQ(split_by_comma[2], "c++17");
    EXPECT_EQ(split_by_comma[3], "c++20");
    EXPECT_EQ(split_by_comma[4], std::string_view{});
}
