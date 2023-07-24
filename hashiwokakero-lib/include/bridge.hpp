#pragma once

#include <utility>

#include "island.hpp"
#include "boardposition.hpp"

struct Bridge
{
    BoardPosition first;
    BoardPosition second;

    bool operator==(const Bridge &right) const;
};