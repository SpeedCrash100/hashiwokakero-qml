#pragma once

#include <memory>
#include <random>
#include <vector>

#include "board.hpp"
#include "bridge.hpp"
#include "island.hpp"

/// @brief Build random board for playing game
class BoardBuilder {
 private:
  std::random_device m_rd;
  std::default_random_engine m_re;

  int m_width;
  int m_height;

  std::vector<std::vector<int>> m_matrix;
  std::vector<Island> m_islands;

 public:
  BoardBuilder();

  void setWidth(int width);
  void setHeight(int height);

  std::shared_ptr<Board> build(int steps);

 private:
  Island pickRandomIsland();
  bool drawBridge(int dir, Island island);
  bool availableToBuild(int x, int y);
};
