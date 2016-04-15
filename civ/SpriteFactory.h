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
#include "SDLManager.h"
#include "Sprite.h"

class SpriteFactory{

	std::map<std::string, SDL_Surface*>	baseImgs;

public:
								SpriteFactory(void);
								~SpriteFactory(void);
	void						AddImage(const std::string& path, const std::string& name);
	void						AddTransparent(uint8_t rT, uint8_t gT, uint8_t bT);
	std::unique_ptr<Sprite>		CreateSprite(const std::string& name, const Rect& dim);
	std::unique_ptr<Sprite>		CreateDiamondSprite(const std::string& name, int x, int y);
};

