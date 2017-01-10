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
#include "SDLEngine.h"
#include "SDLException.h"
#include "Definitions.h"

class SDLSprite{
	friend class	Renderer;

	SDL_Texture*	texture;
	SDL_Rect		rect;

public:
					SDLSprite(void);
					SDLSprite(const Rect& dim);
					SDLSprite(const SDLSprite& src, const Rect& dim_);
					SDLSprite(SDL_Surface* src, const Rect& dim_);
					SDLSprite(const SDLSprite& s);

					SDLSprite(SDLSprite&& other) noexcept;
	SDLSprite&		operator=(SDLSprite&& other) noexcept;
		
					~SDLSprite(void);
	void			Add(const SDLSprite& sprite, const Rect& dim);
	void			Add(const SDLSprite& sprite);
	void			SetAsRenderTarget();
	void			Render(int x, int y);
	Uint32			GetFormat(void) const;
	const SDL_Rect&	GetRect() const;
	RGBAColor		PixelAt(int x, int y);
};

