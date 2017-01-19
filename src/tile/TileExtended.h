#pragma once

#include <memory>

#include "Tile.h"
#include "Tileset.h"
#include "engine/Sprite.h"

class TileExtended: public Tile{
public:
	TileExtended(const Tileset& tileset_);
	~TileExtended();

	void CreateTileSprite(uint8_t neighbourMask) override;
};

