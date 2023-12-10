#include "string.hpp"

#include <string_view>
#include <vector>

std::vector<std::string_view> Utils::String::split(const std::string_view str, char delim) {
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

std::vector<std::string_view> Utils::String::split(const std::string_view str, const std::string_view delim) {
    using Size = std::string_view::size_type;
    std::vector<std::string_view> result{};
    Size last_pos = 0;
    for (Size current_pos = 0; current_pos != std::string_view::npos;) {
        current_pos = str.find(delim, last_pos);
        if (current_pos != std::string_view::npos) {
            result.push_back(str.substr(last_pos, current_pos));
            last_pos = current_pos + delim.size();
        }
    }
    result.push_back(str.substr(last_pos));
    return result;
}