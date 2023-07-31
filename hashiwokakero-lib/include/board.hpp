#pragma once

#include <memory>
#include <random>
#include <vector>

#include "bridge.hpp"
#include "island.hpp"

/// Max size of bridge, i.e. max number of lines between islands
const int MAX_BRIDGE_SIZE = 2;

/// @brief minimal interface for different boards in hashiwokakero
class Board {
 public:
  /// @brief gets width of the board
  /// @return width of the board
  virtual int width() const = 0;

  /// @brief gets height of the board
  /// @return height of the board
  virtual int height() const = 0;

  /// @brief checks if board solved correctly
  /// @return true if board solved
  virtual bool solved() const = 0;

  /// @brief try to build bridge between two islands
  /// @param one first island to connect
  /// @param another second island to connect
  /// @return true if bridge have been built
  ///
  ///
  ///
  /// @warning
  /// Can fail build bridge with false result:
  ///   * No direct line between island (x_1 != x_2 && y_1 != y_2);
  ///   * Island don't exists;
  ///   * Bridge overlaps with existing one;
  virtual bool tryBuildBridge(Island one, Island another) = 0;

  virtual std::vector<Bridge> bridges() = 0;
  virtual std::vector<Island> islands() = 0;
};
