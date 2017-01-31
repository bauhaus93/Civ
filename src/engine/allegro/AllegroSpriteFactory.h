#pragma once

#include <map>
#include <string>
#include <memory>

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
	void			AddSpriteSheet(const std::string& sheetname, const std::string& filename);
	void			MakeTransparent(const RGBColor& color);
	std::shared_ptr<AllegroSprite>	CreateSprite(const std::string& sheetname, const Rect& dim);
	std::shared_ptr<AllegroSprite>	CreateDiamondSprite(const std::string& sheetname, const Point& pos);
};
