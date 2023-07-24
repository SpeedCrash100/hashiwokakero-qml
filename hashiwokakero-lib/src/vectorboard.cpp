#include "vectorboard.hpp"

#include <stdexcept>

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
    if (one == another)
    {
        return false;
    }

    throw std::runtime_error("unimplemented");
    return false;
}

std::vector<Bridge> VectorBoard::bridges()
{
    return m_bridges;
}

std::vector<Island> VectorBoard::islands()
{
    return m_islands;
}
