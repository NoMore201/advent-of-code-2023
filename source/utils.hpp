#pragma once

#include <algorithm>
#include <charconv>
#include <concepts>
#include <iterator>
#include <optional>
#include <set>
#include <stack>
#include <stdexcept>
#include <string_view>
#include <vector>

namespace Utils {

template <typename Container>
concept Iterable = requires(Container container) {
    requires std::forward_iterator<typename Container::iterator>;
    container.begin();
    container.end();
};

template <typename T> std::set<T> find_common_items(const Iterable auto &first, const Iterable auto &second) {
    std::set<T> result{};
    std::for_each(first.begin(), first.end(), [&second, &result](const T &item) {
        if (std::find(second.begin(), second.end(), item) != second.end()) {
            result.insert(item);
        }
    });
    return result;
}

template <typename T>
    requires std::integral<T>
struct ParseResult {
    T final_number{};
    std::ptrdiff_t iterator_offset{};
};

template <typename T>
    requires std::integral<T>
std::optional<ParseResult<T>> try_parse_number(std::string_view str) {
    T final_number{};
    const auto *begin = str.data();
    const auto *end = &*str.end();
    auto parse_result = std::from_chars(begin, end, final_number);
    if (parse_result.ec == std::errc()) {
        const auto pointer_offset = std::distance(begin, parse_result.ptr);
        return {ParseResult<T>{final_number, pointer_offset}};
    }

    return {};
}

std::vector<std::string_view> split(std::string_view str, char delim);

std::vector<std::string_view> split(std::basic_string_view<char>::const_iterator begin,
                                    std::basic_string_view<char>::const_iterator end, char delim);

template <typename I>
    requires std::integral<I>
I parse_integer(std::basic_string_view<char>::const_iterator begin,
                std::basic_string_view<char>::const_iterator end) {
    auto parse_result = try_parse_number<I>(std::string_view{begin, end});
    if (!parse_result) {
        throw std::runtime_error("Error while parsing value from string");
    }
    return (*parse_result).final_number;
}

template <typename I>
    requires std::integral<I>
I parse_integer(std::string_view str) {
    return parse_integer<I>(str.begin(), str.end());
}

template <typename I>
    requires std::integral<I>
I parse_integer(std::basic_string<char>::const_iterator begin, std::basic_string<char>::const_iterator end) {
    return parse_integer<I>(std::string_view{begin, end});
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
