#pragma once

#include <string>

#ifdef _WIN32
#include <sdl/SDL.h>
#endif
#ifdef __linux__
#include <SDL2/SDL.h>
#endif

#include "exception/GameException.h"


class SDLException : public GameException{

public:
	explicit SDLException(const std::string& task);
};
