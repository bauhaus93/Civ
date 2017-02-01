#pragma once

#include <string>
#include <cassert>

#include <allegro5/allegro.h>

#include "common/Rect.h"
#include "common/Point.h"
#include "AllegroEngine.h"
#include "AllegroException.h"

class AllegroSprite{
	ALLEGRO_BITMAP* bmp;
	Dimension		size;
	uint32_t		hash;


public:
					AllegroSprite();
	explicit		AllegroSprite(const Dimension& size_);
					AllegroSprite(const AllegroSprite& sprite) = delete;
					AllegroSprite(const AllegroSprite& sprite, const Rect& srcRect);

	explicit		AllegroSprite(const std::string& filename);
					AllegroSprite(AllegroSprite&& other) noexcept;
	AllegroSprite&	operator=(AllegroSprite&& other) noexcept;
					~AllegroSprite();

	void			MakeColorTransparent(const RGBColor& color);
	int				GetWidth() const;
	int				GetHeight() const;
	void			Add(const AllegroSprite& add);
	void			Add(const AllegroSprite& add, const Point& src, const Point& dest);
	void			Render(int x, int y) const;
	void			SetAsRenderTarget();
	RGBAColor		PixelAt(int x, int y);
	
	void 			CalculateHash();
	uint32_t		GetHash() const;
};
