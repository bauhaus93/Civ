#pragma once

#include <chrono>
#include <string>
#include <sstream>

#include "Common.h"
#include "Map.h"
#include "FPSHandler.h"
#include "Renderer.h"

class Game{

	Map							map;
	FPSHandler					fps;
	Renderer&					renderer;
	uint64_t					ticks;
	unsigned int				fpsCheckInterval;
	unsigned int				lastRenderTime;

public:
				Game(void);
				~Game(void);

	int			Mainloop(void);
	void		Tick(void);
	void		Render(void);

};

