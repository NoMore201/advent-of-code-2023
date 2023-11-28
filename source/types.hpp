#pragma once

#include <stack>
#include <string>
#include <string_view>
#include <vector>

namespace AdventOfCode {

using StringList = std::vector<std::string>;
using StringViewList = std::vector<std::string_view>;

template<typename T>
using StackList = std::vector<std::stack<T>>;

} // namespace AdventOfCode