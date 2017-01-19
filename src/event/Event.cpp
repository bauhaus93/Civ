#include "Event.h"

Event::Event(EventType type_, int flags_):
	type{ type_ },
	flags{ flags_ }{
}

Event::Event(EventType type_):
	type{ type_ },
	flags{ 0 }{
}

Event::Event(EventType type_, Key key_):
	type{ type_ },
	flags{ 0 },
	key{ key_ }{
}
Event::Event(EventType type_, const Point& point_):
	type{ type_ },
	flags{ 0 },
	point{ point_ }{
}

Event::Event(EventType type_, const Mouse& mouse_):
	type{ type_ },
	flags{ 0 },
	mouse{ mouse_ }{
}

Event::~Event(){
}
