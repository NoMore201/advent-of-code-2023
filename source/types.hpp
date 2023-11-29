#pragma once

#include <stack>
#include <string>
#include <string_view>
#include <vector>

namespace AoC {

using StringList = std::vector<std::string>;
using StringViewList = std::vector<std::string_view>;

template<typename T>
using StackList = std::vector<std::stack<T>>;

} // namespace AoC