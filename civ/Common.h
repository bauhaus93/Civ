#pragma once

#include <iostream>
#include <string>

#ifdef _WIN32
	#include <sdl\SDL.h>
#endif
#ifdef __linux__
	#include <SDL/SDL.h>
#endif

namespace common{

	void Error(const std::string& error);
	void Log(const std::string& msg);

};
