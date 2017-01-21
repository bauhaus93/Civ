#include "Rect.h"

Rect::Rect(int x_, int y_, int w_, int h_) :
	x{ x_ },
	y{ y_ },
	w{ w_ },
	h{ h_ }{
}

Rect::Rect(const Rect& other) :
	x{ other.x },
	y{ other.y },
	w{ other.w },
	h{ other.h }{
}

Rect::Rect(const Point& p, int w_, int h_):
	x{ p.x},
	y{ p.y},
	w{ w_},
	h{ h_}{
}
