#pragma once


#include <vector>
#include <numeric>
#include <random>
#include <algorithm>
#include <iostream>
#include <cmath>

#include "exception/CivException.h"

class SimplexNoise{


    const uint32_t      seed;
    std::mt19937        rng;
    std::vector<uint8_t>    permutation;

    double              Fade(double t);
    double              Lerp(double t, double a, double b);
    double              Gradient(int hash, double x, double y, double z);

public:
                SimplexNoise();
                SimplexNoise(uint32_t seed_);
                ~SimplexNoise();

    uint32_t    GetSeed() const;
    double      GetNoise(double x, double y);
    double      GetOctavedNoise(int x, int y, int octaves, double roughness, double scale);
};
