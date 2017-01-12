#pragma once

#include <string>

#ifdef _WIN32
#include <sdl/SDL.h>
#endif
#ifdef __linux__
#include <SDL2/SDL.h>
#endif

#include "Exception/GameException.h"


class SDLException : public GameException{

public:
	SDLException(const std::string& task);
};

