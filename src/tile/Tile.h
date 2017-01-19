#pragma once

#include <memory>
#include <vector>

#include "Tileset.h"
#include "engine/Sprite.h"

enum class TileExtensions{
	RIVER,
	STREET
	//etc
};



class Tile{

protected:
	const Tileset& tileset;
	const Sprite& floor;
	int resource;

	std::unique_ptr<Sprite> sprite;
	std::vector<TileExtensions> extensions;

public:

					Tile(const Tileset& tileset_);
					Tile(const Tile& other) = delete;
	virtual			~Tile(void);

	virtual void	CreateTileSprite(uint8_t neighbourMask) = 0;
	void			AddSprite(const Sprite& add);
	const Tileset&	GetTileset(void){ return tileset; }

	void			Render(int x, int y);
};





