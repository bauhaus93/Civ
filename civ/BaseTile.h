#pragma once

#include "Sprite.h"

class BaseTile{

	Sprite&		floor;

public:
	BaseTile(Sprite& floor_);


	void Render(int x, int y);

};
