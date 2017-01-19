#include "Color.h"


RGBColor::RGBColor() :
	r{ 0 },
	g{ 0 },
	b{ 0 }{
}

RGBColor::RGBColor(uint8_t r_, uint8_t g_, uint8_t b_) :
	r{ r_ },
	g{ g_ },
	b{ b_ }{
}

RGBColor::RGBColor(const RGBColor& other) :
	r{ other.r },
	g{ other.g },
	b{ other.b }{
}

RGBAColor::RGBAColor() :
	r{ 0 },
	g{ 0 },
	b{ 0 },
	a{ 0 }{
}

RGBAColor::RGBAColor(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t a_) :
	r{ r_ },
	g{ g_ },
	b{ b_ },
	a{ a_ }{
}

RGBAColor::RGBAColor(const RGBAColor& other) :
	r{ other.r },
	g{ other.g },
	b{ other.b },
	a{ other.a }{
}