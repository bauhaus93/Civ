#pragma once

#include <memory>

#include <allegro5\allegro.h>

#include "Definitions.h"
#include "CivException.h"
#include "AllegroException.h"
#include "Engine.h"
#include "Log.h"

class AllegroEngine: public Engine{


	ALLEGRO_DISPLAY* display;

	AllegroEngine(const Rect& screen, std::string& windowName);
	~AllegroEngine(void);

public:

	static void Start(int screenW, int screenH, std::string& windowName);

};



