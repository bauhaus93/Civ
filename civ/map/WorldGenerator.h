#pragma once

#include <vector>
#include <memory>

#include "Grid.h"
#include "Node.h"
#include "Common.h"
#include "Tile/Tileset.h"
#include "Tile/Tile.h"
#include "Tile/TileSimple.h"
#include "Tile/TileExtended.h"


class WorldGenerator{
public:
	WorldGenerator();
	~WorldGenerator();

	void Generate(Grid& grid, std::vector<Tileset>& tilesets);
};

