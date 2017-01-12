#pragma once

#include "Engine.h"

#ifdef ENGINE_SDL

#include "SDL/SDLSpriteFactory.h"

typedef SDLSpriteFactory SpriteFactory;

#endif

#ifdef ENGINE_ALLEGRO

#include "Allegro/AllegroSpriteFactory.h"

typedef AllegroSpriteFactory SpriteFactory;

#endif