#pragma once

#include <cstdint>

//Neighbour and shift size in NeighbourMask must be the same direction

enum class Neighbour : uint8_t{
    NE = 0,
    SE = 1,
    SW = 2,
    NW = 3,
    N = 4,
    E = 5,
    S = 6,
    W = 7
};
