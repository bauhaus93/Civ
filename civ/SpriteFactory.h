#pragma once


#include "Engine.h"

#ifdef ENGINE_SDL

#include "SDLSpriteFactory.h"

typedef SDLSpriteFactory SpriteFactory;

#endif

#ifdef ENGINE_ALLEGRO

#include "AllegroSpriteFactory.h"

typedef AllegroSpriteFactory Sprite;

#endif