#include "vectorboard.hpp"

#include <stdexcept>
#include <algorithm>

int VectorBoard::width() const
{
    return m_width;
}

int VectorBoard::height() const
{
    return m_height;
}

bool VectorBoard::solved() const
{
    for (auto island : m_islands)
    {
        if (island.bridgesRemaining != 0)
        {
            return false;
        }
    }

    // TODO! Check that all islands reachable from any location

    return true;
}

bool VectorBoard::tryBuildBridge(Island one, Island another)
{
    // Avoid loops
    if (one == another)
    {
        return false;
    }

    if (!one.connectableWith(another))
    {
        return false;
    }

    auto bridge_option = getBridgeBetween(one.position, another.position);

    if (bridge_option)
    {
        auto bridge = bridge_option.value();
        if (bridge.size == MAX_BRIDGE_SIZE)
        {
            deleteBridge(bridge);
            return true;
        }
        else
        {
            upgradeBridge(bridge);
            return true;
        }
    }

    return createBridge(one.position, another.position);
}

std::vector<Bridge> VectorBoard::bridges()
{
    return m_bridges;
}

std::vector<Island> VectorBoard::islands()
{
    return m_islands;
}

std::optional<Bridge> VectorBoard::getBridgeBetween(BoardPosition pos1, BoardPosition pos2) const
{
    auto out = std::optional<Bridge>();

    Bridge bridge_to_find = Bridge(pos1, pos2);

    if (auto it = std::find(m_bridges.begin(), m_bridges.end(), bridge_to_find); it != m_bridges.end())
    {
        return *it;
    }

    return out;
}

bool VectorBoard::createBridge(BoardPosition pos1, BoardPosition pos2)
{
    // ASSUME: there are no bridges constructed between pos1 and pos2
    // We checked it in VectorBoard::tryBuildBridge()
    if (checkForObstacles(pos1, pos2))
    {
        return false;
    }

    auto bridge = Bridge(pos1, pos2);
    applyToLine(pos1, pos2, [](int x)
                { return x - 1; });
    updateRequirements(pos1);
    updateRequirements(pos2);
    m_bridges.push_back(bridge);

    return true;
}

void VectorBoard::upgradeBridge(Bridge bridge)
{
    // ASSUME: we can increment size of bridge without getting value above MAX_BRIDGE_SIZE
    if (auto it = std::find(m_bridges.begin(), m_bridges.end(), bridge); it != m_bridges.end())
    {
        it->size++;
        applyToLine(bridge.first, bridge.second, [](int x)
                    { return x - 1; });
        updateRequirements(bridge.first);
        updateRequirements(bridge.second);
    }
}

void VectorBoard::deleteBridge(Bridge bridge)
{
    if (auto it = std::find(m_bridges.begin(), m_bridges.end(), bridge); it != m_bridges.end())
    {
        applyToLine(bridge.first, bridge.second, [it](int x)
                    { return x + it->size; });

        updateRequirements(bridge.first);
        updateRequirements(bridge.second);

        m_bridges.erase(it);
    }
}

void VectorBoard::applyToLine(BoardPosition pos1, BoardPosition pos2, std::function<int(int)> fun)
{
    int step_x = 0, step_y = 0;
    if ((pos2.x - pos1.x) != 0)
    {
        step_x = (pos2.x - pos1.x) / abs(pos2.x - pos1.x);
    }

    if ((pos2.y - pos1.y) != 0)
    {
        step_y = (pos2.y - pos1.y) / abs(pos2.y - pos1.y);
    }

    if (step_x != 0 && step_y != 0)
    {
        throw std::runtime_error("pos1 and pos2 must be connectable");
    }

    auto pos_x = pos1.x;
    auto pos_y = pos1.y;

    while (pos_x != pos2.x || pos_y != pos2.y)
    {
        m_matrix[pos_x][pos_y] = fun(m_matrix[pos_x][pos_y]);

        pos_x += step_x;
        pos_y += step_y;
    }

    m_matrix[pos_x][pos_y] = fun(m_matrix[pos2.x][pos2.y]);
}

bool VectorBoard::checkForObstacles(BoardPosition pos1, BoardPosition pos2)
{
    int step_x = 0, step_y = 0;
    if ((pos2.x - pos1.x) != 0)
    {
        step_x = (pos2.x - pos1.x) / abs(pos2.x - pos1.x);
    }

    if ((pos2.y - pos1.y) != 0)
    {
        step_y = (pos2.y - pos1.y) / abs(pos2.y - pos1.y);
    }

    if (step_x != 0 && step_y != 0)
    {
        throw std::runtime_error("pos1 and pos2 must be connectable");
    }

    // Ignore islands
    auto pos_x = pos1.x + step_x;
    auto pos_y = pos1.y + step_y;

    while (pos_x != pos2.x || pos_y != pos2.y)
    {
        if (m_matrix[pos_x][pos_y] < 0)
        {
            return true;
        }

        pos_x += step_x;
        pos_y += step_y;
    }

    return false;
}

void VectorBoard::updateRequirements(BoardPosition pos)
{
    if (auto it = std::find(m_islands.begin(), m_islands.end(), Island(pos)); it != m_islands.end())
    {
        it->bridgesRemaining = m_matrix[it->position.x][it->position.y];
    }
}
