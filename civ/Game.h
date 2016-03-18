#pragma once

#include <chrono>
#include <string>
#include <sstream>

#ifdef _WIN32
	#include <sdl\SDL.h>
#endif
#ifdef __linux__
	#include <SDL2/SDL.h>
#endif

#include "Common.h"
#include "Map.h"
#include "FPSHandler.h"

class Game{

	Map							map;
	FPSHandler					fps;
	uint64_t					ticks;
	uint32_t					fpsCheckInterval;

public:
				Game(void);
				~Game(void);

	int			Mainloop(void);
	void		Tick(void);
	void		Render(void);

};

