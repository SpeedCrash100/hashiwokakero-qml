#pragma once

struct BoardPosition
{
    int x;
    int y;

    BoardPosition(int x, int y);

    bool operator==(const BoardPosition &right) const;
};
