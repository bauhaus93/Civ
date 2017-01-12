#pragma once

#include <chrono>
#include <string>
#include <sstream>
#include <queue>

#include "Common.h"
#include "Map/Map.h"
#include "FPSHandler.h"

class Game{

	Map				map;
	FPSHandler		fps;
	uint64_t		ticks;
	unsigned int	fpsCheckInterval;
	unsigned int	lastRenderTime;

	void		Tick(void);
	void		HandleEvents(void);
	void		MouseEvent(Event& e);
	void		Render(void);

public:
				Game(void);
				~Game(void);

	int			Mainloop(void);

};

