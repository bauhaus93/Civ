#pragma once

#include <memory>
#include <map>

#include "engine/SpriteFactory.h"
#include "tile/Tileset.h"
#include "tile/Tile.h"
#include "Grid.h"
#include "WorldGenerator.h"
#include "common/Rect.h"

#define RESOURCE_CHANCE (10)


class Map{

	Rect											drawField;
	int												drawSizeY;
	SpriteFactory									spriteFactory;
	Grid											grid;
	std::vector<Tileset>							tilesets;
	
	bool change;

	void		LoadTilesets();

public:
				Map(const Rect& drawField_);
				~Map();

	void		Clicked(int screenX, int screenY);
	void		Render();
};

