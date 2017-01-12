#pragma once

//Definitions are set by cmake
//#define ENGINE_SDL
//#define ENGINE_ALLEGRO


#ifdef ENGINE_SDL
	#ifdef ENGINE_ALLEGRO
		#error Cannot use both SDL and Allegro!
	#endif
#endif

#ifdef ENGINE_SDL

#include "sdl/SDLEngine.h"

typedef SDLEngine Engine;

#endif

#ifdef ENGINE_ALLEGRO

#include "allegro/AllegroEngine.h"

typedef AllegroEngine Engine;

#endif
