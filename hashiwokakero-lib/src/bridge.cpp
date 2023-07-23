#include "bridge.hpp"

bool Bridge::operator==(const Bridge &right) const
{
    auto left = *this;

    return (left.first == right.first && left.second == right.second) ||
           (left.first == right.second && left.second == right.first);
}
