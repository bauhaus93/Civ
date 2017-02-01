#pragma once

#include <memory>
#include <vector>

#include "tileset/BasicTerrainset.h"
#include "tileset/TilesetType.h"
#include "engine/Sprite.h"
#include "engine/SpriteManager.h"

class Tile{

	const BasicTerrainset& 	terrainset;
	int						basicSpriteID;
	int 					resourceID;

	std::shared_ptr<const Sprite> sprite;

public:

	explicit				Tile(const BasicTerrainset& tileset_);
							Tile(const Tile& other) = delete;
							~Tile() = default;

	void					UpdateSprite(uint8_t terrainNeighbourMask);
	void 					RandomizeBaseSprite(std::mt19937& rng);
	void 					RandomizeResource(std::mt19937& rng);
	const BasicTerrainset&	GetTerrainset(){ return terrainset; }

	void					Render(int x, int y);
};
