#include "boardbuilder.hpp"

#include <random>
#include <stdexcept>
#include <algorithm>

#include "vectorboard.hpp"

enum DrawBridgeDirections
{
    Up = 0,
    Down,
    Left,
    Right,

    DrawBridgeDirections_SIZE
};

const double START_CHANCE_TO_DRAW_BRIDGE = 0.9;
const double DECREMENT_CHANCE = 0.1;
const int MAX_RETRY_TO_DRAW_BRIDGE = 100;

BoardBuilder::BoardBuilder()
{
    m_re = std::default_random_engine(m_rd());

    m_width = 10;
    m_height = 10;
}

void BoardBuilder::setWidth(int width)
{
    if (width < 3)
    {
        throw std::range_error("the width is too small");
    }
    m_width = width;
}

void BoardBuilder::setHeight(int height)
{
    if (height < 3)
    {
        throw std::range_error("the height is too small");
    }
    m_height = height;
}

std::shared_ptr<Board> BoardBuilder::build(int steps)
{
    // Prepare matrix
    m_matrix = {};
    m_matrix.resize(m_width);
    std::fill(m_matrix.begin(), m_matrix.end(), std::vector<int>(m_height, 0));
    // Prepare islands list
    m_islands = {};
    m_islands.reserve(steps + 1);

    // Select random point for first island
    std::random_device rd;
    std::default_random_engine re(rd());
    auto width_dist = std::uniform_int_distribution<int>(0, m_width - 1);
    auto height_dist = std::uniform_int_distribution<int>(0, m_height - 1);
    auto start_position = BoardPosition(width_dist(re), height_dist(re));

    auto start_island = Island(start_position);
    m_islands.push_back(start_island);

    for (int i = 0; i < steps; i++)
    {
        auto island = pickRandomIsland();
        auto select_dir = std::uniform_int_distribution<int>(0, DrawBridgeDirections_SIZE - 1);
        auto dir = select_dir(m_re);

        int retry_count = MAX_RETRY_TO_DRAW_BRIDGE;
        while (!drawBridge(dir, island) && retry_count-- > 0)
        {
            island = pickRandomIsland();
            select_dir = std::uniform_int_distribution<int>(0, DrawBridgeDirections_SIZE - 1);
            dir = select_dir(m_re);
        };

        if (retry_count <= 0)
        {
            throw std::runtime_error("cannot draw bridge. may be too many steps specified");
        }
    }

    // Prepare islands vector
    for (auto &island : m_islands)
    {
        auto bridge_req = m_matrix[island.position.x][island.position.y];
        island.bridgeRequired = bridge_req;
        island.bridgesRemaining = bridge_req;
    }

    auto result_board = std::make_shared<VectorBoard>();
    result_board->m_width = m_width;
    result_board->m_height = m_height;
    result_board->m_bridges = {};
    result_board->m_islands = m_islands;
    auto &result_matrix = result_board->m_matrix;
    result_matrix = {};
    result_matrix.resize(m_width);

    return result_board;
}

Island BoardBuilder::pickRandomIsland()
{
    auto dist = std::uniform_int_distribution<int>(0, std::distance(m_islands.begin(), m_islands.end()) - 1);
    auto it = m_islands.begin();
    std::advance(it, dist(m_re));

    return *it;
}

bool BoardBuilder::drawBridge(int dir, Island island)
{
    auto bridge_size_dist = std::uniform_int_distribution<int>(1, MAX_BRIDGE_SIZE);
    auto bridge_size = bridge_size_dist(m_re);

    int step_x = 0, step_y = 0;

    switch (dir)
    {
    case DrawBridgeDirections::Up:
        step_y = -1;
        break;
    case DrawBridgeDirections::Down:
        step_y = 1;
        break;
    case DrawBridgeDirections::Left:
        step_x = -1;
        break;
    case DrawBridgeDirections::Right:
        step_x = 1;
        break;
    }

    int cur_x = island.position.x;
    int next_x = cur_x + step_x;

    int cur_y = island.position.y;
    int next_y = cur_y + step_y;

    // We need to go at least one step: we will place loop to 1 island
    if (!availableToBuild(next_x, next_y))
    {
        return false;
    }

    m_matrix[cur_x][cur_y] += bridge_size;
    cur_x += step_x;
    next_x += step_x;
    cur_y += step_y;
    next_y += step_y;

    int cur_size = 2;

    auto prob_to_continue_dist = std::bernoulli_distribution(START_CHANCE_TO_DRAW_BRIDGE);

    while (availableToBuild(next_x, next_y) && prob_to_continue_dist(m_re))
    {
        m_matrix[cur_x][cur_y] += bridge_size;

        cur_x += step_x;
        next_x += step_x;
        cur_y += step_y;
        next_y += step_y;
        cur_size++;

        auto new_chance = START_CHANCE_TO_DRAW_BRIDGE - (double)cur_size * DECREMENT_CHANCE;
        if (new_chance < 0.0)
        {
            new_chance = 0.0;
        }
        prob_to_continue_dist = std::bernoulli_distribution(new_chance);
    }

    m_matrix[cur_x][cur_y] += bridge_size;
    Island new_island = Island(BoardPosition(cur_x, cur_y));
    m_islands.push_back(new_island);

    return true;
}

bool BoardBuilder::availableToBuild(int x, int y)
{
    if (x < 0 || y < 0)
    {
        return false;
    }

    if (m_width <= x || m_height <= y)
    {
        return false;
    }

    if (m_matrix[x][y] > 0) // Means there are bridge have been built already or there are island
    {
        return false;
    }

    return true;
}
