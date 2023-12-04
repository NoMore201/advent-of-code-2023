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
concept Iterable = requires (Container a){
    requires std::forward_iterator<typename Container::iterator>;
    a.begin();
    a.end();
};

template <typename T>
std::set<T> find_common_items(const Iterable auto& first, const Iterable auto& second) {
    std::set<T> result{};
    std::for_each(first.begin(), first.end(), [&second, &result](const T& item){
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
std::optional<ParseResult<T>> try_parse_number(std::basic_string_view<char>::iterator begin,
                                               std::basic_string_view<char>::iterator end) {
    const auto begin_ptr = &*begin;
    const auto end_ptr = &*end;
    int final_number{};
    auto parse_result = std::from_chars(begin_ptr, end_ptr, final_number);
    if (parse_result.ec == std::errc()) {
        auto pointer_offset = std::distance(begin_ptr, parse_result.ptr);
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
