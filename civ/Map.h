#pragma once

#include <memory>
#include <map>

#include "SpriteFactory.h"
#include "Tileset.h"
#include "Tile.h"
#include "Grid.h"
#include "WorldGenerator.h"
#include "Definitions.h"

#define RESOURCE_CHANCE (10)


class Map{

	Rect											drawField;
	int												drawSizeY;
	SpriteFactory									spriteFactory;
	Grid											grid;
	std::vector<Tileset>							tilesets;
	
	bool change;

	void		LoadTilesets(void);

public:
				Map(const Rect& drawField_);
				~Map(void);

	void		Clicked(int screenX, int screenY);
	void		Render(void);
};

