#pragma once

#include <memory>




#include "Sprite.h"

class Tile{

	std::unique_ptr<Sprite> sprite;
	bool hasResource;

public:

	Tile();
	~Tile();

	void SetSprite(std::unique_ptr<Sprite> sprite_);
	void SetResource(bool value){ hasResource = value; }
	void Render(int x, int y);
};





