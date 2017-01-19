#pragma once

#include "common/Point.h"
#include "Key.h"
#include "Mouse.h"

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
		Key key;
		Mouse mouse;
	};

	Event(EventType type_, int flags_);
	Event(EventType type_);

	Event(EventType type_, const Point& point_);
	Event(EventType type_, Key key_);
	Event(EventType type_, const Mouse& mouse_);
	~Event();

};
