#pragma once

#include <utility>

#include "island.hpp"
#include "boardposition.hpp"

struct Bridge
{
    BoardPosition first;
    BoardPosition second;

    int size;

    Bridge(BoardPosition pos1, BoardPosition pos2);

    bool operator==(const Bridge &right) const;
};