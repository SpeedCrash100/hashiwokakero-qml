#include "island.hpp"

Island::Island(BoardPosition position)
    : position(position), bridgeRequired(0), bridgesRemaining(0) {}

Island::Island(BoardPosition position, int req)
    : position(position), bridgeRequired(req), bridgesRemaining(req) {}

bool Island::connectableWith(const Island& other) const {
  return (position.row == other.position.row) || (position.col == other.position.col);
}

bool Island::operator==(const Island& right) const {
  return position == right.position;
}