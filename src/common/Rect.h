#pragma once

#include "Point.h"

struct Rect{
	int x;
	int y;
	int w;
	int h;

	Rect(int x_, int y_, int w_, int h_);
	Rect(const Rect& other);
	Rect(const Point& p, int w_, int h_);

};
