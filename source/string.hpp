#pragma once

#include <string_view>
#include <vector>

namespace Utils {

namespace String {

std::vector<std::string_view> split(std::string_view str, char delim);

std::vector<std::string_view> split(std::string_view str, std::string_view delim);

} // namespace String

} // namespace Utils