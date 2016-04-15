#pragma once

#include <memory>
#include <map>

#include "SpriteFactory.h"
#include "Tileset.h"
#include "TilesetSimple.h"
#include "Tile.h"
#include "Grid.h"
#include "Node.h"


class Map{

	Rect											drawField;
	SpriteFactory									spriteFactory;
	std::map<TileType, std::unique_ptr<Tileset>>	tileset;
	Grid											grid;

	void LoadTilesets();

public:
	Map(const Rect& screen);
	~Map(void);

	void Render(void);
};

