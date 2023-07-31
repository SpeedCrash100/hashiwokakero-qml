#include "boardposition.hpp"

BoardPosition::BoardPosition(int x, int y) : x(x), y(y) {}

bool BoardPosition::operator==(const BoardPosition& right) const {
  return x == right.x && y == right.y;
}