#pragma once

#include <inttypes.h>

struct RGBColor{
	uint8_t r;
	uint8_t g;
	uint8_t b;

	RGBColor();
	RGBColor(uint8_t r_, uint8_t g_, uint8_t b_);
	RGBColor(const RGBColor& other);
};

struct RGBAColor{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	RGBAColor();
	RGBAColor(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t a_);
	RGBAColor(const RGBAColor& other);

};

