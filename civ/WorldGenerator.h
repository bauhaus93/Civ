#pragma once

#include <vector>
#include <memory>

#include "Grid.h"
#include "Tileset.h"
#include "Node.h"
#include "Tile.h"
#include "TileSimple.h"
#include "TileExtended.h"
#include "Common.h"

class WorldGenerator{
public:
	WorldGenerator();
	~WorldGenerator();

	void Generate(Grid& grid, std::vector<Tileset>& tilesets);
};

