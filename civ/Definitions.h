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

	Rect(const Rect& other){
		x = other.x;
		y = other.y;
		w = other.w;
		h = other.h;
	}
};

struct RGBColor{
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

struct RGBAColor{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
};