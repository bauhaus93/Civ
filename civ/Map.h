#pragma once

#include <memory>

#include "SpriteFactory.h"


class Map{

	SpriteFactory	spriteFactory;
	std::unique_ptr<Sprite>	sprite;

public:
	Map(void);
	~Map(void);
	void Render(void);
};

