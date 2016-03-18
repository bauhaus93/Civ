#pragma once

#include <string>
#include <sdl\SDL.h>

#include "Common.h"
#include "SDLManager.h"
#include "CivExceptions.h"

class Sprite{

	SDL_Texture*	texture;
	SDL_Rect		rect;

public:
					Sprite(SDL_Surface* src, const SDL_Rect& dim);
					Sprite(const Sprite&, const SDL_Rect& dim);
					~Sprite(void);
	void			Render(int x, int y);
	Uint32			GetFormat(void) const;
};

