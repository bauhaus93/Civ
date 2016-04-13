#pragma once

#include <memory>
#include <vector>

#include "Sprite.h"

typedef uint8_t TileType;

enum class TileExtensions{
	RIVER,
	STREET
	//etc
};



class Tile{

	TileType type;
	Sprite& floor;
	int resource;

	std::unique_ptr<Sprite> sprite;
	std::vector<TileExtensions> extensions;

public:

				Tile(TileType type_, Sprite& floor_);
				Tile(const Tile& other) = delete;
				~Tile(void);

	void		SetResource(int newResource);
	void		InitializeSprite(void);
	void		AddSprite(Sprite& add);

	int			GetResource(void) const;

	void		Render(int x, int y);
};





