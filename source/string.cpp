#include "string.hpp"

#include <string_view>
#include <vector>

std::vector<std::string_view> Utils::String::split(const std::string_view str, char delim) {
    using Size = std::string_view::size_type;
    std::vector<std::string_view> result{};
    Size last_pos = 0;
    for (Size current_pos = 0; current_pos != std::string_view::npos;) {
        current_pos = str.find(delim, last_pos);
        if (current_pos != std::string_view::npos) {
            const auto length = current_pos - last_pos;
            result.push_back(str.substr(last_pos, length));
            last_pos = current_pos + 1;
        }
    }
    result.push_back(str.substr(last_pos));
    return result;
}

std::vector<std::string_view> Utils::String::split(const std::string_view str, const std::string_view delim) {
    using Size = std::string_view::size_type;
    std::vector<std::string_view> result{};
    Size last_pos = 0;
    for (Size current_pos = 0; current_pos != std::string_view::npos;) {
        current_pos = str.find(delim, last_pos);
        if (current_pos != std::string_view::npos) {
            const auto length = current_pos - last_pos;
            result.push_back(str.substr(last_pos, length));
            last_pos = current_pos + delim.size();
        }
    }
    result.push_back(str.substr(last_pos));
    return result;
}