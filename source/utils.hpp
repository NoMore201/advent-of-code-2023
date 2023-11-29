#pragma once

#include "types.hpp"

#include <algorithm>
#include <charconv>
#include <iterator>
#include <ranges>
#include <set>
#include <stack>
#include <stdexcept>
#include <string_view>
#include <vector>

namespace AdventOfCode {

auto find_common_items(std::ranges::forward_range auto &first, std::ranges::forward_range auto &second) {
    return first | std::views::filter([&second](auto item) {
        return std::find(second.begin(), second.end(), item) != second.end();
    });
}

template <typename T> std::set<T> range_to_set(std::ranges::forward_range auto &rng) {
    return std::set<T>(rng.begin(), rng.end());
}

// TODO: make generic?
StringViewList split(std::string_view str, char delim);

void from_chars_wrapper(const std::string_view str, auto &value) {
    auto result = std::from_chars(str.data(), str.data() + str.size(), value);
    if (result.ec != std::errc()) {
        throw std::runtime_error("Error while parsing value from string");
    }
}

template <typename T> std::stack<T> reverse_stack(std::stack<T> &original) {
    std::stack<T> reversed{};
    const auto original_size = original.size();
    for (std::stack<char>::size_type count = 0; count < original_size; count++) {
        const auto top = original.top();
        original.pop();
        reversed.push(top);
    }
    return reversed;
}

} // namespace AdventOfCode
