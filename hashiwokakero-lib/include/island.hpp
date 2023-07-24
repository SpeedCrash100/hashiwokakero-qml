#pragma once

#include "boardposition.hpp"

struct Island
{
    BoardPosition position;

    int bridgeRequired;
    int bridgesRemaining;

    Island(BoardPosition position);

    bool operator==(const Island &island) const;
};
