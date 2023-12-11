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

/**
 * Parse sequence of numbers from string. Numbers can be separated by any separator.
 * @tparam T Integer type
 * @param str String containing a sequence of numbers
 * @return Vector containing all the numbers in the provided string
 */
template<typename T>
    requires std::integral<T>
std::vector<T> parse_list(std::string_view str) {
    using Size = std::string_view::size_type;

    std::vector<T> number_list{};
    for (Size index = 0; index < str.size();) {
        auto result = try_parse_number<T>(str.substr(index));
        if (result) {
            number_list.push_back(result->final_number);
            index += static_cast<Size>(result->iterator_offset);
        } else {
            ++index;
        }
    }

    return number_list;
}


} // namespace Utils
