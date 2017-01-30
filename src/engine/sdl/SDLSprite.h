#pragma once

#include <string>
#include <iostream>


#ifdef _WIN32
	#include <sdl/SDL.h>
#endif
#ifdef __linux__
	#include <SDL2/SDL.h>
#endif

#include "common/Common.h"
#include "SDLEngine.h"
#include "SDLException.h"
#include "common/Color.h"
#include "common/Rect.h"

class SDLSprite{
	friend class	Renderer;

	SDL_Texture*	texture;
	SDL_Rect		rect;

public:
					SDLSprite();
	explicit		SDLSprite(const Dimension& size);
					SDLSprite(SDL_Surface* src, const Rect& dim_);

					SDLSprite(SDLSprite&& other) noexcept;
	SDLSprite&		operator=(SDLSprite&& other) noexcept;

					~SDLSprite();
	void			Add(const SDLSprite& sprite, const Point& src, const Point& dest);
	void			Add(const SDLSprite& sprite);
	void			SetAsRenderTarget();
	void			Render(int x, int y);
	Uint32			GetFormat() const;
	const SDL_Rect&	GetRect() const;
	RGBAColor		PixelAt(int x, int y);
	int				GetWidth() const;
	int				GetHeight() const;
};
