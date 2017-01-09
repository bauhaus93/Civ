#pragma once

#include <inttypes.h>

struct Rect{
	int x;
	int y;
	int w;
	int h;

	Rect(int x_, int y_, int w_, int h_):
		x{ x_ },
		y{ y_ },
		w{ w_ },
		h{ h_ }{
	}

	Rect(const Rect& other) :
		x{ other.x },
		y{ other.y },
		w{ other.w },
		h{ other.h }{
	}
	
};

struct Point{
	int x;
	int y;

	Point(int x_, int y_) :
		x{ x_ },
		y{ y_ }{
	}

	Point(const Rect& other) :
		x{ other.x },
		y{ other.y }{
	}


};

typedef Point Dimension;

struct RGBColor{
	uint8_t r;
	uint8_t g;
	uint8_t b;

	RGBColor(uint8_t r_, uint8_t g_, uint8_t b_) :
		r{ r_ },
		g{ g_ },
		b{ b_ }{
	}

	RGBColor(const RGBColor& other) :
		r{ other.r },
		g{ other.g },
		b{ other.b }{
	}
};

struct RGBAColor{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	RGBAColor(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t a_) :
		r{ r_ },
		g{ g_ },
		b{ b_ },
		a{ a_ }{
	}

	RGBAColor(const RGBAColor& other) :
		r{ other.r },
		g{ other.g },
		b{ other.b },
		a{ other.a }{
	}



};

