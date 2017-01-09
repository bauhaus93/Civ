#pragma once

#include "Engine.h"

#ifdef ENGINE_SDL

#include "SDLSprite.h"

typedef SDLSprite Sprite;

#endif

#ifdef ENGINE_ALLEGRO

#include "AllegroSprite.h"

typedef AllegroSprite Sprite;

#endif


