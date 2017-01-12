#pragma once

#include "Engine.h"

#ifdef ENGINE_SDL

#include "sdl/SDLSprite.h"

typedef SDLSprite Sprite;

#endif

#ifdef ENGINE_ALLEGRO

#include "allegro/AllegroSprite.h"

typedef AllegroSprite Sprite;

#endif


