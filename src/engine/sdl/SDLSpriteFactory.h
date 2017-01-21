#pragma once

#include <string>
#include <map>
#include <memory>

#ifdef _WIN32
	#include <sdl/SDL.h>
#endif
#ifdef __linux__
	#include <SDL2/SDL.h>
#endif

#include "SDLException.h"
#include "SDLEngine.h"
#include "SDLSprite.h"

class SDLSpriteFactory{

	std::map<std::string, SDL_Surface*>	baseImgs;

public:
				SDLSpriteFactory();
				~SDLSpriteFactory();
	void		AddSpriteSheet(const std::string& filename, const std::string& sheetname);
	void		MakeTransparent(const RGBColor& color);
	SDLSprite	CreateSprite(const std::string& sheetname, const Rect& dim);
	SDLSprite	CreateDiamondSprite(const std::string& sheetname, const Point& pos);
};
