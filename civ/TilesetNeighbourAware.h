#pragma once

#include <string>

#include "Tileset.h"

class TilesetNeighbourAware :
	public Tileset{
public:
	TilesetNeighbourAware(unsigned int resourceChance_);
	~TilesetNeighbourAware();
};

