#pragma once

#include <map>
#include <memory>

#include <sdl\SDL.h>

#include "CivExceptions.h"
#include "Sprite.h"

class SpriteFactory{

	std::map<std::string, SDL_Surface*>	baseImgs;

public:
								SpriteFactory(void);
								~SpriteFactory(void);
	void						AddImage(const std::string& path, const std::string& name);
	std::unique_ptr<Sprite>		CreateSprite(const std::string& name, const SDL_Rect& dim, uint32_t colorKey);
	std::unique_ptr<Sprite>		CreateDiamondSprite(const std::string& name, int x, int y, uint32_t colorKey);
};

