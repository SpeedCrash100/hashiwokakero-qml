#pragma once

#include "boardposition.hpp"

struct Island {
  BoardPosition position;

  int bridgeRequired;
  int bridgesRemaining;

  Island(BoardPosition position);
  Island(BoardPosition position, int req);

  /// @brief check if it is possible to connect this island with an other one
  /// @param other the other island
  /// @return true if it is possible, false otherwise
  ///
  /// @warning
  /// check only if there direct horizontal or vertical line between islands
  bool connectableWith(const Island& other) const;

  bool operator==(const Island& island) const;
};
