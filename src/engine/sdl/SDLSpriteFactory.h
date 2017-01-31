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
	void		AddSpriteSheet(const std::string& sheetname, const std::string& filename);
	void		MakeTransparent(const RGBColor& color);
	std::shared_ptr<SDLSprite>	CreateSprite(const std::string& sheetname, const Rect& dim);
	std::shared_ptr<SDLSprite>	CreateDiamondSprite(const std::string& sheetname, const Point& pos);
};
