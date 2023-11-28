#pragma once

#include "types.hpp"

#include <algorithm>
#include <charconv>
#include <iterator>
#include <set>
#include <stack>
#include <stdexcept>
#include <string_view>
#include <vector>

namespace AdventOfCode {

template <typename T, typename FirstIt, typename SecondIt>
    requires std::forward_iterator<FirstIt> && std::forward_iterator<SecondIt>
std::set<T> find_common_items(FirstIt first_begin, FirstIt first_end, SecondIt second_begin,
                              SecondIt second_end) {
    std::set<T> result{};
    std::for_each(first_begin, first_end, [second_begin, second_end, &result](T item) {
        if (std::find(second_begin, second_end, item) != second_end) {
            result.insert(item);
        }
    });
    return result;
}

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
