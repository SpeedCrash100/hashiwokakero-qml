#pragma once

#include <functional>
#include <optional>
#include <vector>

#include "board.hpp"
#include "bridge.hpp"
#include "island.hpp"

/// @brief private implementation of board based on vector-based matrix
class VectorBoard : public Board {
 public:
  std::vector<std::vector<int>> m_matrix;
  std::vector<Bridge> m_bridges;
  std::vector<Island> m_islands;
  int m_width;
  int m_height;

  int width() const override;
  int height() const override;

  bool solved() const override;

  bool tryBuildBridge(Island one, Island another) override;

  std::vector<Bridge> bridges() override;
  std::vector<Island> islands() override;

 private:
  std::optional<Bridge> getBridgeBetween(BoardPosition pos1,
                                         BoardPosition pos2) const;

  bool createBridge(BoardPosition pos1, BoardPosition pos2);
  void upgradeBridge(Bridge bridge);
  void deleteBridge(Bridge bridge);

  void applyToLine(BoardPosition pos1, BoardPosition pos2,
                   std::function<int(int)> fun);
  bool checkForObstacles(BoardPosition pos1, BoardPosition pos2);

  void updateRequirements(BoardPosition pos);
};