#pragma once

#include <vector>
#include <memory>
#include <random>

#include "Grid.h"
#include "Node.h"
#include "SimplexNoise.h"
#include "common/Common.h"
#include "tile/Tile.h"
#include "tile/TileFactory.h"
#include "Log.h"


class WorldGenerator{

	const TileFactory& 	tileFactory;

	std::mt19937 		rng;

	SimplexNoise 		landmassNoise;
	SimplexNoise 		temperatureNoise;
	SimplexNoise 		moistureNoise;
	SimplexNoise 		elevationNoise;

	bool				IsMountain(double elevation, double temperature, double moisture);
	bool				IsHills(double elevation, double temperature, double moisture);
	bool 				IsDesert(double elevation, double temperature, double moisture);
	bool 				IsPrairie(double elevation, double temperature, double moisture);
	bool 				IsJungle(double elevation, double temperature, double moisture);
	bool 				IsSwamp(double elevation, double temperature, double moisture);
	bool 				IsForest(double elevation, double temperature, double moisture);
	bool 				IsArctic(double elevation, double temperature, double moisture);
	bool 				IsTundra(double elevation, double temperature, double moisture);

public:
						WorldGenerator(const TileFactory& tileFactory_, uint32_t seed);
						~WorldGenerator() = default;

	void 				Generate(Grid& grid);
	void 				CalculateNode(Node& node);
};
