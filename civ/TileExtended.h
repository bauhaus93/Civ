#pragma once

#include "Tile.h"
#include "Tileset.h"
#include "Sprite.h"

class TileExtended: public Tile{
public:
	TileExtended(const Tileset& tileset_);
	~TileExtended();

	void CreateTileSprite(uint8_t neighbourMask) override;
};

