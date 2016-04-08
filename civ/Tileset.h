#pragma once

#include <vector>
#include <string>
#include <memory>


#include "Tile.h"
#include "Sprite.h"


typedef uint8_t TileType;

enum class NeighbourInfo{
	DIFFERENT = 0,
	SAME = 1
};

enum class NeighbourDiamond{
	TOP_RIGHT = 1,
	BOT_RIGHT = 2,
	BOT_LEFT = 4,
	TOP_LEFT = 8,

	TOP = 16,
	RIGHT = 32,
	BOT = 64,
	LEFT = 128
};


class Tileset{
	
protected:
	unsigned int		resourceChance;

public:
	Tileset(unsigned int resourceChance_);

	virtual ~Tileset() = default;

	virtual void InitiateTile(Tile& tile) = 0;
	virtual void CreateTileSprite(Tile& tile) = 0;

};



