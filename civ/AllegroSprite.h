#pragma once

#include <string>

#include <allegro5\allegro.h>

#include "Definitions.h"
#include "AllegroEngine.h"
#include "AllegroException.h"

class AllegroSprite{
	ALLEGRO_BITMAP* bmp;
	int index;


public:
					AllegroSprite();
					AllegroSprite(const AllegroSprite& sprite, const Rect& rect);
					AllegroSprite(const Rect& rect);
					AllegroSprite(const std::string& filename);
					AllegroSprite(AllegroSprite&& other) noexcept;
					AllegroSprite(const AllegroSprite& other);
	AllegroSprite&	operator=(AllegroSprite&& other) noexcept;
					~AllegroSprite();

	void			MakeColorTransparent(const RGBColor& color);
	int				GetWidth(void) const;
	int				GetHeight(void) const;
	void			Add(const AllegroSprite& add);
	void			Add(const AllegroSprite& add, const Rect& rect);
	void			Render(int x, int y);
	void			SetAsRenderTarget(void);
	RGBAColor		PixelAt(int x, int y);
};

