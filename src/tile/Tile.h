#pragma once

#include <memory>
#include <vector>

#include "tileset/BasicTerrainset.h"
#include "engine/Sprite.h"

class Tile{

	const BasicTerrainset& 	terrainset;
	int						basicSpriteID;
	int 					resourceID;
	uint8_t					terrainNeighbourMask;

	std::unique_ptr<Sprite> sprite;

public:

							Tile(const BasicTerrainset& tileset_);
							Tile(const Tile& other) = delete;
							~Tile() = default;

	void					CreateSprite();
	void					AddSprite(const Sprite& add);
	void 					UpdateTerrainNeighbourMask(uint8_t newMask);
	const BasicTerrainset&	GetTerrainset(){ return terrainset; }

	void					Render(int x, int y);
};
