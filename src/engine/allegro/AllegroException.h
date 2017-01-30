#pragma once

#include <string>

#include <allegro5/allegro.h>

#include "exception/GameException.h"

class AllegroException: public GameException{
public:
	explicit AllegroException(const std::string& task);
	~AllegroException();
};
