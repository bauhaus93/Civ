#pragma once

#include <memory>

#include "SpriteFactory.h"
#include "TileFactory.h"
#include "Tileset.h"

class Map{

	SpriteFactory	spriteFactory;
	TileFactory		tileFactory;

	std::unique_ptr<BaseTile>	tile;
	std::unique_ptr<Sprite>		sprite;

public:
	Map(void);
	~Map(void);
	void Render(void);
};

