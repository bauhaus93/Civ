#pragma once

#include <map>
#include <string>

#include <allegro5/allegro.h>

#include "AllegroSprite.h"
#include "common/Rect.h"
#include "common/Color.h"
#include "AllegroException.h"

class AllegroSpriteFactory{
	std::map<std::string, AllegroSprite>	sprites;

public:
					AllegroSpriteFactory();
					~AllegroSpriteFactory();
	void			AddSpriteSheet(const std::string& filename, const std::string& sheetname);
	void			MakeTransparent(const RGBColor& color);
	AllegroSprite	CreateSprite(const std::string& sheetname, const Rect& dim);
	AllegroSprite	CreateDiamondSprite(const std::string& sheetname, const Point& pos);
};
