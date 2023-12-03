#pragma once

#include <algorithm>
#include <charconv>
#include <concepts>
#include <iterator>
#include <ranges>
#include <set>
#include <stack>
#include <stdexcept>
#include <string_view>
#include <vector>

namespace Utils {

auto find_common_items(std::ranges::forward_range auto &first, std::ranges::forward_range auto &second) {
    return first | std::views::filter([&second](auto item) {
        return std::find(second.begin(), second.end(), item) != second.end();
    });
}

template <typename T> std::set<T> range_to_set(std::ranges::forward_range auto &rng) {
    return std::set<T>(rng.begin(), rng.end());
}

std::vector<std::string_view> split(std::string_view str, char delim);

std::vector<std::string_view> split(std::basic_string_view<char>::const_iterator begin,
                                    std::basic_string_view<char>::const_iterator end, char delim);

template <typename I>
    requires std::integral<I>
I parse_integer(std::basic_string_view<char>::const_iterator begin,
                std::basic_string_view<char>::const_iterator end) {
    I integer{};
    const auto *begin_ptr = &*begin;
    const auto length = std::distance(begin, end);

    auto result = std::from_chars(begin_ptr, begin_ptr + length, integer);
    if (result.ec != std::errc()) {
        throw std::runtime_error("Error while parsing value from string");
    }

    return integer;
}

template <typename I>
    requires std::integral<I>
I parse_integer(std::string_view str) {
    return parse_integer<I>(str.begin(), str.end());
}

template <typename I>
    requires std::integral<I>
I parse_integer(std::basic_string<char>::const_iterator begin, std::basic_string<char>::const_iterator end) {
    return parse_integer<I>(std::string_view{std::move(begin), std::move(end)});
}

template <typename T> std::stack<T> reverse_stack(std::stack<T> &original) {
    // TODO: should the original be consumed ?
    std::stack<T> reversed{};
    const auto original_size = original.size();
    for (std::stack<char>::size_type count = 0; count < original_size; count++) {
        const auto top = original.top();
        original.pop();
        reversed.push(top);
    }
    return reversed;
}

} // namespace Utils
