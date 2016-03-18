#pragma once

#include <chrono>
#include <string>
#include <sstream>

#include <sdl\SDL.h>

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

