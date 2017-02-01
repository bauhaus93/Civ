#pragma once

#include <chrono>
#include <string>
#include <sstream>
#include <queue>

#include "common/Common.h"
#include "map/Map.h"
#include "FPSHandler.h"
#include "event/Event.h"
#include "event/Key.h"
#include "event/Mouse.h"

class Game{

	std::unique_ptr<Map>	map;
	FPSHandler				fps;
	uint64_t				ticks;
	unsigned int			fpsCheckInterval;
	unsigned int			lastRenderTime;

	void		Tick();
	void 		HandleFPS();
	void		HandleEvents();
	void		HandleMouseEvent(Event& e);
	void		Render();

public:
				Game();
				~Game();

	int			Mainloop();

};
