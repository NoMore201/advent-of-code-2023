#include "utils.hpp"

AoC::StringViewList AoC::split(const std::string_view str, char delim) {
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