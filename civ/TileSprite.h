#pragma once

#include <memory>

#ifdef _WIN32
#include <sdl/SDL.h>
#endif
#ifdef __linux__
#include <SDL2/SDL.h>
#endif

#include "Sprite.h"

class TileSprite{

	Sprite		sprite;

public:
				TileSprite();
				~TileSprite();
	void		Render(int x, int y);
	void		AddSprite(const Sprite& sprite);

};



