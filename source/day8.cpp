#include "day8.hpp"
#include "utils.hpp"

#include <gsl/assert>

#include <cstdint>
#include <map>
#include <numeric>
#include <string_view>
#include <utility>

namespace {

using Size = std::size_t;

enum class Command : uint8_t { Left, Right };

using CommandList = std::vector<Command>;

bool ends_with(std::string_view input, char character) { return input.back() == character; }

struct PathChoice {
    std::string left;
    std::string right;

    std::string take(Command command) const {
        if (command == Command::Left) {
            return left;
        }
        if (command == Command::Right) {
            return right;
        }
        throw std::runtime_error("Invalid command");
    }
};

using PathMap = std::map<std::string, PathChoice>;

CommandList parse_commands(std::string_view line) {
    CommandList result{};
    for (char cmd_string : line) {
        if (cmd_string == 'L') {
            result.push_back(Command::Left);
        } else if (cmd_string == 'R') {
            result.push_back(Command::Right);
        } else {
            throw std::runtime_error("Unknown command supplied");
        }
    }
    return result;
}

void strip_extra_chars_from(std::string &string) {
    const auto to_be_erased = {' ', '(', ')'};
    for (const char item : to_be_erased) {
        Size current_pos = 0;
        while ((current_pos = string.find(item)) != std::string_view::npos) {
            string.erase(current_pos, 1);
        }
    }
}

PathMap parse_map(const std::vector<std::string_view> &lines) {
    PathMap result{};

    for (auto line : lines) {
        std::string current_line{line.begin(), line.end()};
        strip_extra_chars_from(current_line);
        const auto split = Utils::split(current_line, '=');
        Ensures(split.size() == 2);
        const auto path_choices = Utils::split(split[1], ',');
        result.emplace(std::string{split[0].begin(), split[0].end()},
                       PathChoice{std::string{path_choices[0].begin(), path_choices[0].end()},
                                  std::string{path_choices[1].begin(), path_choices[1].end()}});
    }

    return result;
}

struct CommandIterator {

    using Iterator = CommandList::const_iterator;

    Iterator begin;
    Iterator end;
    Iterator current;

    explicit CommandIterator(const CommandList &command_list)
        : begin(command_list.begin()), end(command_list.end()), current(end) {}

    Iterator next() {
        if (current == end) {
            current = begin;
        }
        return current++;
    }
};

std::vector<std::string> get_start_keys(const PathMap &path_map) {
    std::vector<std::string> result{};

    std::for_each(path_map.begin(), path_map.end(), [&result](const auto &pair) {
        if (ends_with(pair.first, 'A')) {
            result.push_back(pair.first);
        }
    });

    return result;
}

struct PathIterator {

    Size count{0};
    CommandIterator iterator;
    PathMap::const_iterator map_begin;
    PathMap::const_iterator map_end;
    std::string current_key;

    explicit PathIterator(CommandIterator iter, const PathMap &path_map, std::string start_key)
        : iterator(iter), map_begin(path_map.cbegin()), map_end(path_map.cend()),
          current_key(std::move(start_key)) {}

    const PathChoice &find_next_choice(const std::string &key) const {
        auto choice_iter =
            std::find_if(map_begin, map_end, [key](const auto &pair) { return pair.first == key; });
        if (choice_iter == map_end) {
            throw std::runtime_error("Key not found in std::map");
        }
        return choice_iter->second;
    }

    Size find_next_end() {
        while (true) {
            count++;
            auto current_command = *iterator.next();
            const auto &next_choice = find_next_choice(current_key);
            current_key = next_choice.take(current_command);
            if (ends_with(current_key, 'Z')) {
                break;
            }
        }
        return count;
    }
};

} // anonymous namespace

std::size_t AoC::day8_solution_part1(std::string_view input) {
    const auto split_by_empty_line = Utils::split(input, "\n\n");
    const auto commands = parse_commands(split_by_empty_line[0]);
    const auto path_map = parse_map(Utils::split(split_by_empty_line[1], '\n'));

    CommandIterator iterator{commands};
    std::string current_key = "AAA";
    Size count = 0;

    while (true) {
        count++;
        auto current_command = iterator.next();
        const auto &choices = path_map.at(current_key);
        current_key = choices.take(*current_command);
        if (current_key == "ZZZ") {
            break;
        }
    }

    return count;
}

std::size_t AoC::day8_solution_part2(std::string_view input) {

    const auto split_by_empty_line = Utils::split(input, "\n\n");
    const auto commands = parse_commands(split_by_empty_line[0]);
    const auto path_map = parse_map(Utils::split(split_by_empty_line[1], '\n'));

    const CommandIterator iterator{commands};
    auto current_keys = get_start_keys(path_map);
    std::vector<PathIterator> path_iterators{};

    std::transform(current_keys.begin(), current_keys.end(), std::back_inserter(path_iterators),
                   [iterator, &path_map](const std::string &key) {
        return PathIterator{iterator, path_map, key};
    });

    // try the lcm approach
    std::vector<Size> count_points;
    count_points.reserve(path_iterators.size());
    for (auto & path_iterator : path_iterators) {
        count_points.push_back(path_iterator.find_next_end());
    }

    Ensures(count_points.size() > 1);
    auto lcm = std::accumulate(count_points.begin() + 1, count_points.end(), count_points[0], [](Size final, Size current) {
        return std::lcm(final, current);
    });

    return lcm;
}
