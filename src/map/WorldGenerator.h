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
	SimplexNoise 		elevationNoise;
	SimplexNoise 		temperatureNoise;
	SimplexNoise 		moistureNoise;

	double				elevationMod;
	double				temperatureMod;
	double				moistureMod;


	void 				CalculateNode(Node& node);

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
	void 				Generate(Grid& grid, double elevationMod_, double temperatureMod_, double moistureMod_);

};

inline bool WorldGenerator::IsMountain(double elevation, double temperature, double moisture){
	return elevation > 0.8 && elevation > 0.5 * temperature && elevation > 0.5 * moisture;
}

inline bool WorldGenerator::IsHills(double elevation, double temperature, double moisture){
	return elevation > 0.7 && elevation > 0.75 * moisture;
}

inline bool WorldGenerator::IsDesert(double elevation, double temperature, double moisture){
	return temperature > 0.75 && moisture < 0.4;
}

inline bool WorldGenerator::IsPrairie(double elevation, double temperature, double moisture){
	return temperature > 0.4 && moisture < 0.33;
}

inline bool WorldGenerator::IsJungle(double elevation, double temperature, double moisture){
	return temperature > 0.75 && moisture > 0.5;
}

inline bool WorldGenerator::IsSwamp(double elevation, double temperature, double moisture){
	return temperature > 0.3 && temperature < 0.6 && moisture > 0.7 && elevation < 0.4;
}

inline bool WorldGenerator::IsForest(double elevation, double temperature, double moisture){
	return temperature > 0.25 && temperature < 0.5 && moisture > 0.4 && elevation > 0.4;
}

inline bool WorldGenerator::IsArctic(double elevation, double temperature, double moisture){
	return temperature < 0.15;
}

inline bool WorldGenerator::IsTundra(double elevation, double temperature, double moisture){
	return temperature < 0.20 && moisture > 0.25;
}
