#pragma once

struct Island
{
    int x;
    int y;
    int bridgeRequired;
    int bridgesRemaining;

    Island(int x, int y);

    bool operator==(const Island &island) const;
};
