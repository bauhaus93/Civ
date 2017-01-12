#pragma once

#include <memory>

#include "Tile.h"
#include "Tileset.h"
#include "Engine/Sprite.h"

class TileSimple: public Tile{

public:
	TileSimple(const Tileset& tileset_);
	~TileSimple();
	void CreateTileSprite(uint8_t neighbourMask) override;
};

