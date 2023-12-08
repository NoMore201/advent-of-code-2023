#include "utils.hpp"

#include <string_view>
#include <vector>

std::vector<std::string_view> Utils::split(const std::string_view str, char delim) {
    using Iterator = std::string_view::const_iterator;
    std::vector<std::string_view> result{};
    Iterator begin = str.begin();

    for (Iterator current = str.cbegin(); current != str.end(); ++current) {
        if (*current == delim) {
            result.emplace_back(begin, current);
            begin = current + 1;
        }
    }

    result.emplace_back(begin, str.end());

    return result;
}

std::vector<std::string_view> Utils::split(std::string_view str, std::string_view delim) {
    using Size = std::string_view::size_type;
    Size find_pos{};
    Size begin_pos{};
    std::vector<std::string_view> result{};
    auto current_string = str;
    while ((find_pos = current_string.find(delim)) != std::string_view::npos) {
        result.push_back(str.substr(begin_pos, find_pos - begin_pos));
        begin_pos = find_pos + delim.size();
        current_string = current_string.substr(begin_pos);
    }
    result.push_back(current_string);
    return result;
}