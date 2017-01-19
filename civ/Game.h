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
