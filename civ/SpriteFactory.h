#pragma once

#include <map>
#include <memory>

#ifdef _WIN32
	#include <sdl\SDL.h>
#endif
#ifdef __linux__
	#include <SDL2/SDL.h>
#endif

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

