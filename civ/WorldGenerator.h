#pragma once

#include <vector>
#include <memory>

#include "Grid.h"
#include "Tileset.h"

class WorldGenerator{
public:
	WorldGenerator();
	~WorldGenerator();

	void Generate(Grid& grid, std::vector<Tileset>& tilesets);
};

