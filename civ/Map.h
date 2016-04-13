#pragma once

#include <memory>
#include <map>

#include "SpriteFactory.h"
#include "Tileset.h"
#include "TilesetSimple.h"
#include "Tile.h"
#include "Grid.h"


class Map{

	SpriteFactory									spriteFactory;
	std::map<TileType, std::unique_ptr<Tileset>>	tileset;
	Grid											grid;

	std::unique_ptr<Tile>	tile;

	void LoadTilesets();

public:
	Map(void);
	~Map(void);

	void Render(void);
};

