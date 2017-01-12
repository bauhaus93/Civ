#pragma once

#include "Engine.h"

#ifdef ENGINE_SDL

#include "sdl/SDLSpriteFactory.h"

typedef SDLSpriteFactory SpriteFactory;

#endif

#ifdef ENGINE_ALLEGRO

#include "allegro/AllegroSpriteFactory.h"

typedef AllegroSpriteFactory SpriteFactory;

#endif
