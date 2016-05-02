#pragma once

#include <chrono>
#include <string>
#include <sstream>

#include "Common.h"
#include "Map.h"
#include "FPSHandler.h"

class Game{

	Map				map;
	FPSHandler		fps;
	uint64_t		ticks;
	unsigned int	fpsCheckInterval;
	unsigned int	lastRenderTime;

	void		Tick(void);
	void		WindowEvent(SDL_Event& e);
	void		MouseEvent(SDL_Event & e);
	void		Render(void);

public:
				Game(void);
				~Game(void);

	int			Mainloop(void);

};

