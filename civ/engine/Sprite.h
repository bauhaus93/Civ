#pragma once

#include "Engine.h"

#ifdef ENGINE_SDL

#include "SDL/SDLSprite.h"

typedef SDLSprite Sprite;

#endif

#ifdef ENGINE_ALLEGRO

#include "Allegro/AllegroSprite.h"

typedef AllegroSprite Sprite;

#endif


