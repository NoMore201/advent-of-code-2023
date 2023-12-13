#include "day10.hpp"
#include "string.hpp"

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
constexpr char starting_position = 'S';

enum class Direction : std::uint8_t { North, West, South, East };

using Record = std::tuple<Direction, char>;
using History = std::vector<Record>;

class TileMap {

public:
    struct Position {
        Size row;
        Size column;
    };

private:
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
    Position m_current_position{};
    std::vector<std::string_view> m_map;
    Size m_max_rows;
    Size m_max_columns;

public:
    explicit TileMap(std::string_view input)
        : m_map(Utils::String::split(input, '\n')), m_max_rows(m_map.size()),
          m_max_columns(m_map.at(0).size()) {
        bool found = false;
        for (Size row = 0; row < m_map.size(); ++row) {
            for (Size column = 0; column < m_map.at(0).size(); ++column) {
                if (m_map.at(row).at(column) == starting_position) {
                    m_current_position = {row, column};
                    found = true;
                    break;
                }
            }
        }
        Ensures(found);
    }

    char at(Position position) const { return m_map.at(position.row).at(position.column); }

    const Position &current_position() const noexcept { return m_current_position; }

    Position get_next_position(Direction movement) const {
        if (movement == Direction::North && m_current_position.row > 0) {
            return {m_current_position.row - 1, m_current_position.column};
        }
        if (movement == Direction::East && m_current_position.column < m_max_columns - 1) {
            return {m_current_position.row, m_current_position.column + 1};
        }
        if (movement == Direction::South && m_current_position.row < m_max_rows - 1) {
            return {m_current_position.row + 1, m_current_position.column};
        }
        if (movement == Direction::West && m_current_position.column > 0) {
            return {m_current_position.row, m_current_position.column - 1};
        }
        throw std::runtime_error("Position not found");
    }

    Direction move_and_validate(Direction direction) {
        const auto next_position = get_next_position(direction);
        const char current_char = at(next_position);
        if (current_char != starting_position) {
            auto next_movement = m_next_direction.at(std::make_tuple(direction, current_char));
            m_current_position = next_position;
            return next_movement;
        }
        m_current_position = next_position;
        return direction;
    }

    /**
     * Try to move in the requested direction
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
        const char current_char = at(next_position);
        try {
            (void)m_next_direction.at(std::make_tuple(direction, current_char));
            return next_position;
        } catch (std::out_of_range &) {
            return {};
        }
    }
};

Direction get_first_movement(const TileMap &map) {
    for (const auto movement : {Direction::North, Direction::East, Direction::South, Direction::West}) {
        auto first_move_pos = map.test_movement(movement);
        if (first_move_pos) {
            return movement;
        }
    }
    throw std::runtime_error("Unable to perform first move: no tile is connected properly");
}

History record_path(TileMap &map) {
    History history{};

    // perform first movement
    auto first_move = get_first_movement(map);
    auto next_move = map.move_and_validate(first_move);
    history.emplace_back(std::make_tuple(first_move, map.at(map.current_position())));

    // iterate until we come back to start position
    while (map.at(map.current_position()) != starting_position) {
        next_move = map.move_and_validate(next_move);
        history.emplace_back(std::make_tuple(next_move, map.at(map.current_position())));
    }

    return history;
}

} // namespace

std::size_t AoC::day10_solution_part1(std::string_view input) {

    TileMap map{input};

    const auto history = record_path(map);
    return history.size() / 2;
}

int AoC::day10_solution_part2(std::string_view input) {
    const auto lines = Utils::String::split(input, '\n');

    int result{};

    return result;
}
