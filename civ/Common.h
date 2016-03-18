#pragma once

#include <iostream>
#include <string>

#include <sdl\SDL.h>

namespace common{

	void Error(const std::string& error);
	void Log(const std::string& msg);

};