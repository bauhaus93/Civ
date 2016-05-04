#pragma once

#include "Sprite.h"

class Resource{

	Sprite& sprite;
public:
	Resource(Sprite& sprite_);
	~Resource();
	Sprite& GetSprite(void) const;
};

