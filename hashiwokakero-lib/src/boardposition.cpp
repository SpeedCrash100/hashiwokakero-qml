#include "boardposition.hpp"

bool BoardPosition::operator==(const BoardPosition &right) const
{
    return x == right.x && y == right.y;
}