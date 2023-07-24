#include "island.hpp"

Island::Island(BoardPosition position) : position(position), bridgeRequired(0), bridgesRemaining(0)
{
}

bool Island::operator==(const Island &right) const
{
    return position == right.position;
}