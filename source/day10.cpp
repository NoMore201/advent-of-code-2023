#include "day10.hpp"
#include "string.hpp"

#include <algorithm>
#include <gsl/assert>
#include <map>
#include <optional>
#include <stdexcept>
#include <string_view>

namespace {

using Size = std::size_t;

constexpr char west_to_east = '-';
constexpr char north_to_south = '|';
constexpr char west_to_south = '7';
constexpr char north_to_east = 'L';
constexpr char north_to_west = 'J';
constexpr char east_to_south = 'F';
constexpr char ground = '.';
constexpr char starting_symbol = 'S';

enum class Direction : std::uint8_t { North, West, South, East };

using Record = std::tuple<Direction, char>;
using History = std::vector<Record>;

class InvalidInput : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class StartPositionReached : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class TileMap {
    std::vector<std::vector<char>> m_tile_map{};
    Size m_max_rows{};
    Size m_max_columns{};

public:
    static bool all_elements_same_size(const std::vector<std::vector<char>> &map) {
        auto iter = std::adjacent_find(map.begin(), map.end(), [](const auto &left, const auto &right) {
            return left.size() != right.size();
        });
        return iter == map.end();
    }

    TileMap() noexcept = default;

    explicit TileMap(const std::string_view input) {
        const auto lines = Utils::String::split(input, '\n');
        for (const auto &line : lines) {
            m_tile_map.emplace_back(line.begin(), line.end());
        }
        if (not all_elements_same_size(m_tile_map)) {
            throw InvalidInput{"Tile map rows have different length"};
        }

        m_max_rows = m_tile_map.size();
        m_max_columns = m_tile_map.at(0).size();
    }

    const char &at(Size row, Size column) const { return m_tile_map.at(row).at(column); };

    Size max_rows() const noexcept { return m_max_rows; }
    Size max_columns() const noexcept { return m_max_columns; }
};

struct Position {
    Size row;
    Size column;
};

class Navigation {

    std::map<Record, Direction> m_next_direction{
        {std::make_tuple(Direction::East, west_to_east), Direction::East},
        {std::make_tuple(Direction::East, west_to_south), Direction::South},
        {std::make_tuple(Direction::East, north_to_west), Direction::North},

        {std::make_tuple(Direction::West, west_to_east), Direction::West},
        {std::make_tuple(Direction::West, east_to_south), Direction::South},
        {std::make_tuple(Direction::West, north_to_east), Direction::North},

        {std::make_tuple(Direction::North, north_to_south), Direction::North},
        {std::make_tuple(Direction::North, east_to_south), Direction::East},
        {std::make_tuple(Direction::North, west_to_south), Direction::West},

        {std::make_tuple(Direction::South, north_to_south), Direction::South},
        {std::make_tuple(Direction::South, north_to_east), Direction::East},
        {std::make_tuple(Direction::South, north_to_west), Direction::West},
    };
    TileMap m_map{};
    Position m_current_position{};

    Position get_next_position(Direction movement) const {
        if (movement == Direction::North && m_current_position.row > 0) {
            return {m_current_position.row - 1, m_current_position.column};
        }
        if (movement == Direction::East && m_current_position.column < m_map.max_columns() - 1) {
            return {m_current_position.row, m_current_position.column + 1};
        }
        if (movement == Direction::South && m_current_position.row < m_map.max_rows() - 1) {
            return {m_current_position.row + 1, m_current_position.column};
        }
        if (movement == Direction::West && m_current_position.column > 0) {
            return {m_current_position.row, m_current_position.column - 1};
        }
        throw std::runtime_error("Position not found");
    }

public:
    void find_and_set_start_position() {
        bool found = false;
        for (Size row = 0; row < m_map.max_rows(); ++row) {
            for (Size column = 0; column < m_map.max_columns(); ++column) {
                if (m_map.at(row, column) == starting_symbol) {
                    m_current_position = {row, column};
                    found = true;
                    break;
                }
            }
        }

        if (not found) {
            throw InvalidInput{"Unable to find start position"};
        }
    }

    void set_tile_map(TileMap map) {
        m_map = std::move(map);
        find_and_set_start_position();
    }

    const Position &current_position() const noexcept { return m_current_position; }
    const TileMap &map() const noexcept { return m_map; }

    Direction follow_pipe_trail(Direction direction) {
        const auto next_position = get_next_position(direction);
        const char current_char = m_map.at(next_position.row, next_position.column);
        if (current_char != starting_symbol) {
            auto next_movement = m_next_direction.at(std::make_tuple(direction, current_char));
            m_current_position = next_position;
            return next_movement;
        }
        m_current_position = next_position;
        throw StartPositionReached("Start position reached");
    }

    /**
     * Check if moving to specified direction is allowed
     * @param direction Direction to move to
     * @return New position if the movement is allowed, nothing otherwise
     */
    std::optional<Position> test_movement(Direction direction) const {
        Position next_position{};
        try {
            next_position = get_next_position(direction);
        } catch (std::runtime_error &) {
            return {};
        }
        const char current_char = m_map.at(next_position.row, next_position.column);
        try {
            (void)m_next_direction.at(std::make_tuple(direction, current_char));
            return next_position;
        } catch (std::out_of_range &) {
            return {};
        }
    }
};

Direction get_first_movement(const Navigation &navigation) {
    for (const auto movement : {Direction::North, Direction::East, Direction::South, Direction::West}) {
        auto first_move_pos = navigation.test_movement(movement);
        if (first_move_pos) {
            return movement;
        }
    }
    throw std::runtime_error("Unable to perform first move: no tile is connected properly");
}

History record_path(Navigation &navigation) {
    History history{};

    const auto &map = navigation.map();

    // perform first movement
    auto first_move = get_first_movement(navigation);
    auto next_move = navigation.follow_pipe_trail(first_move);
    auto current_pos = navigation.current_position();
    history.emplace_back(std::make_tuple(first_move, map.at(current_pos.row, current_pos.column)));

    // iterate until we come back to start position
    try {
        while (true) {
            next_move = navigation.follow_pipe_trail(next_move);
            current_pos = navigation.current_position();
            history.emplace_back(std::make_tuple(next_move, map.at(current_pos.row, current_pos.column)));
        }
    } catch (StartPositionReached &) {
        // save last movement
        current_pos = navigation.current_position();
        history.emplace_back(std::make_tuple(next_move, map.at(current_pos.row, current_pos.column)));
    }

    return history;
}

} // namespace

std::size_t AoC::day10_solution_part1(std::string_view input) {

    TileMap map{input};
    Navigation navigation{};
    navigation.set_tile_map(std::move(map));

    const auto history = record_path(navigation);
    return history.size() / 2;
}

int AoC::day10_solution_part2(std::string_view input) {
    const auto lines = Utils::String::split(input, '\n');

    int result{};

    return result;
}
