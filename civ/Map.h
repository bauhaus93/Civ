#pragma once

#include <memory>
#include <map>

#include "SpriteFactory.h"
#include "Tileset.h"
#include "TilesetSimple.h"
#include "Tile.h"
#include "Grid.h"
#include "Node.h"
#include "Renderer.h"


class Map{

	Rect											drawField;
	SpriteFactory									spriteFactory;
	std::map<TileType, std::unique_ptr<Tileset>>	tileset;
	std::unique_ptr<Grid>							grid;
	bool change;

	void		LoadTilesets();

public:
				Map(const Rect& drawField_);
				~Map(void);

	void		Clicked(int screenX, int screenY);
	void		Render(void);
};

