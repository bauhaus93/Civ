#pragma once

#include <vector>
#include <memory>

#include "Grid.h"
#include "Node.h"
#include "SimplexNoise.h"
#include "common/Common.h"
#include "tile/Tile.h"
#include "tile/TileFactory.h"
#include "Log.h"


class WorldGenerator{
public:
	WorldGenerator();
	~WorldGenerator();

	void Generate(Grid& grid, const TileFactory& tileFactory);
};
