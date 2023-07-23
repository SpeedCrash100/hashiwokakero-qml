#pragma once

#include <utility>

#include "island.hpp"

struct Bridge
{
    Island first;
    Island second;

    bool operator==(const Bridge &right) const;
};

// class Bridge
// {
// private:
//     std::pair<Island, Island> m_pair;

// public:
//     std::pair<Island, Island> islands() const;

//     bool operator==(const Bridge &right) const;
// };