#pragma once

#include <memory>
#include <vector>

#include "Tileset.h"
#include "engine/Sprite.h"

class Tile{

protected:
	const Tileset& 	tileset;
	const Sprite& 	floor;
	int 			resource;

	std::unique_ptr<Sprite> 	sprite;

public:

					Tile(const Tileset& tileset_);
					Tile(const Tile& other) = delete;
	virtual			~Tile();

	virtual void	CreateTileSprite(uint8_t neighbourMask) = 0;
	void			AddSprite(const Sprite& add);
	const Tileset&	GetTileset(){ return tileset; }

	void			Render(int x, int y);
};
