#pragma once

#include <string>


#ifdef _WIN32
	#include <sdl\SDL.h>
#endif
#ifdef __linux__
	#include <SDL2/SDL.h>
#endif

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

