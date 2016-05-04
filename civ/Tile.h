#pragma once

#include <memory>
#include <vector>

#include "Tileset.h"
#include "Sprite.h"

enum class TileExtensions{
	RIVER,
	STREET
	//etc
};



class Tile{

	const Tileset& tileset;
	const Sprite& floor;
	int resource;

	std::unique_ptr<Sprite> sprite;
	std::vector<TileExtensions> extensions;

public:

				Tile(const Tileset& tileset_);
				Tile(const Tile& other) = delete;
				~Tile(void);

	void		InitializeSprite(void);
	void		AddSprite(const Sprite& add);

	void		Render(int x, int y);
};





