#pragma once

#include <inttypes.h>

struct Rect{
	int x;
	int y;
	int w;
	int h;
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