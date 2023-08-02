#include "boardposition.hpp"

BoardPosition::BoardPosition(int x, int y) : row(x), col(y) {}

bool BoardPosition::operator==(const BoardPosition& right) const {
  return row == right.row && col == right.col;
}