#pragma once

#include <vector>
#include <memory>

#include "Grid.h"
#include "Node.h"
#include "SimplexNoise.h"
#include "common/Common.h"
#include "tile/Tileset.h"
#include "tile/Tile.h"
#include "tile/TileSimple.h"
#include "tile/TileExtended.h"



class WorldGenerator{
public:
	WorldGenerator();
	~WorldGenerator();

	void Generate(Grid& grid, std::vector<Tileset>& tilesets);
};
