#pragma once

#include <string>
#include <iostream>


#ifdef _WIN32
	#include <sdl/SDL.h>
#endif
#ifdef __linux__
	#include <SDL2/SDL.h>
#endif

#include "Common.h"
#include "SDLManager.h"
#include "CivExceptions.h"

static void TextureOnTexture(SDL_Texture *src, const SDL_Rect& srcRect, SDL_Texture *dest, const SDL_Rect& destRect);

class Sprite{

	SDL_Texture*	texture;
	SDL_Rect		rect;

public:
					Sprite(const SDL_Rect & dim);
					Sprite(const Sprite& src, const SDL_Rect& dim);
					Sprite(SDL_Surface* src, const SDL_Rect& dim);
					Sprite(const Sprite& s) = delete;
					
					
					
					~Sprite(void);
	void			Add(const Sprite& sprite, const SDL_Rect& dim);
	void			Render(int x, int y);
	Uint32			GetFormat(void) const;
};

