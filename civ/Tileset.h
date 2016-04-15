#pragma once

#include <vector>
#include <string>
#include <memory>


#include "Tile.h"
#include "Sprite.h"


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
	std::string		name;
	TileType		type;
	unsigned int	resourceChance;

public:
	Tileset(const std::string& name_, TileType type_, unsigned int resourceChance_);

	virtual ~Tileset() = default;

	virtual std::unique_ptr<Tile> CreateTile(void) = 0;
	virtual void CreateTileSprite(Tile& tile) = 0;

};
