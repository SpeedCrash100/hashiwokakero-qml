#include "island.hpp"

Island::Island(int x, int y) : x(x), y(y), bridgeRequired(0), bridgesRemaining(0)
{
}

bool Island::operator==(const Island &right) const
{
    return x == right.x && y == right.y;
}