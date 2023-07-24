#include "bridge.hpp"

Bridge::Bridge(BoardPosition pos1, BoardPosition pos2) : first(pos1), second(pos2), size(1)
{
}

bool Bridge::operator==(const Bridge &right) const
{
    auto left = *this;

    return (left.first == right.first && left.second == right.second) ||
           (left.first == right.second && left.second == right.first);
}
