#pragma once

struct BoardPosition {
  int row;
  int col;

  BoardPosition(int row, int col);

  bool operator==(const BoardPosition& right) const;
};
