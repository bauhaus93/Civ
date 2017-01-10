#include "Event.h"

Event::Event(EventType type_, int flags_):
	type{ type_ },
	flags{ flags_ }{
}

Event::Event(EventType type_):
	type{ type_ },
	flags{ 0 }{
}

Event::~Event(){
}