#pragma once

#define ENGINE_SDL
//#define ENGINE_ALLEGRO


#ifdef ENGINE_SDL
	#ifdef ENGINE_ALLEGRO
		#error Can use only one engine!
	#endif
#endif

#ifdef ENGINE_SDL

#include "SDLEngine.h"

typedef SDLEngine Engine;

#endif

#ifdef ENGINE_ALLEGRO

#include "AllegroEngine.h"

typedef AllegroEngine Engine;

#endif