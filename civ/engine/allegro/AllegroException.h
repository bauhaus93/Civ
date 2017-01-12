#pragma once

#include <string>

#include <allegro5/allegro.h>

#include "Exception/GameException.h"

class AllegroException: public GameException{
public:
	AllegroException(const std::string& task);
	~AllegroException();
};

