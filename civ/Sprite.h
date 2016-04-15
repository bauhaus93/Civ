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
#include "Definitions.h"

class Sprite{
	friend class	Renderer;

	SDL_Texture*	texture;
	SDL_Rect		rect;

public:
					Sprite(const Rect& dim);
					Sprite(const Sprite& src, const Rect& dim_);
					Sprite(SDL_Surface* src, const Rect& dim_);
					Sprite(const Sprite& s);
		
					~Sprite(void);
	void			Add(const Sprite& sprite, const Rect& dim);
	void			Add(const Sprite& sprite);
	void			Render(int x, int y);
	Uint32			GetFormat(void) const;
	const SDL_Rect&	GetRect() const;
};

