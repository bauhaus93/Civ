#pragma once

#include <memory>

#include <allegro5\allegro.h>

#include "Definitions.h"
#include "CivException.h"
#include "AllegroException.h"
#include "Log.h"

class AllegroEngine{

	static AllegroEngine* instance;


	ALLEGRO_DISPLAY* display;

	AllegroEngine(const Rect& screen, std::string& windowName);
	~AllegroEngine(void);

public:

	static					void Start(const Rect& screen, std::string& windowName);
	static					void Stop(void);
	static AllegroEngine&	Instance(void);

};

inline AllegroEngine& AllegroEngine::Instance(void){
	return *instance;
}

