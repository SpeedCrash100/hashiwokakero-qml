#pragma once

#include <vector>
#include "board.hpp"
#include "bridge.hpp"
#include "island.hpp"

/// @brief private implementation of board based on vector-based matrix
class VectorBoard : public Board
{
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
};