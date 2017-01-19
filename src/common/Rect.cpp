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