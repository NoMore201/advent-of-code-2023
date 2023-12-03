#include "utils.hpp"

std::vector<std::string_view> AoC::split(const std::string_view str, char delim) {
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

std::vector<std::string_view> AoC::split(std::basic_string_view<char>::const_iterator begin,
                                         std::basic_string_view<char>::const_iterator end, char delim) {
    return split(std::string_view{begin, end}, delim);
}