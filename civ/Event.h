#pragma once

#include "Definitions.h"

enum class EventType{
	KEY_PRESSED,
	MOUSE_PRESSED,
	WINDOW_MINIMIZED,
	WINDOW_RESTORED,
	QUIT
};

struct Event{

	EventType type;
	int flags;

	union{
		Point point;
	};

	Event(EventType type_, int flags_);
	Event(EventType type_);
	~Event();
	
};

