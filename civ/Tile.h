#pragma once

#include <memory>
#include <vector>


#include "Sprite.h"



enum class SubTileType{
	FLOOR,
	ONFLOOR,
	RESOURCE,
};


struct SubTile{
	SubTileType type;
	int index;

	SubTile(SubTileType type_, int index_) : type { type_ }, index { index_ } {}

};


class Tile{

	std::unique_ptr<Sprite> sprite;
	std::vector<SubTile> subTile;


public:

	Tile();
	~Tile();

	void AddSubTile(SubTileType type, int index){ subTile.emplace_back(type, index);}
	void SetSprite(std::unique_ptr<Sprite> sprite_){ sprite = move(sprite_); }

	const std::vector<SubTile>& GetSubTiles() { return subTile; };

	void Render(int x, int y);
};





