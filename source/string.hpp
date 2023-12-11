#pragma once

#include <string_view>
#include <vector>

namespace Utils::String {

std::vector<std::string_view> split(std::string_view str, char delim);

std::vector<std::string_view> split(std::string_view str, std::string_view delim);

} // namespace Utils::String