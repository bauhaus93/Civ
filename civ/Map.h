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

	void		AlignViewPos(int x, int y);
	const Rect&	GetDrawField() const{ return drawField; }

	void		Render(void);
};

