#pragma once

struct Rect{
	int x;
	int y;
	int w;
	int h;

	Rect::Rect(int x_, int y_, int w_, int h_);
	Rect::Rect(const Rect& other);

};
