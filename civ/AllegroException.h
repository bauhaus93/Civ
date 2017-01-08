#pragma once

#include <allegro5\allegro.h>

class AllegroException: public GraphicsException{
public:
	AllegroException(const std::string& task);
	~AllegroException();
};

