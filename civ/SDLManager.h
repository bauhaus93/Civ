#pragma once

#include <string>
#include <sstream>
#include <memory>

#ifdef _WIN32
	#include <sdl/SDL.h>
#endif
#ifdef __linux__
	#include <SDL2/SDL.h>
#endif

#include "Common.h"
#include "CivExceptions.h"
#include "Sprite.h"
#include "Definitions.h"


class SDL{
	
	static SDL*	instance;

	static void Init(void){ Init("LEL", Rect{ 0, 0, 1024, 768 }); };

	SDL_Window		*window;
	SDL_Renderer	*renderer;
	const int		sizeX;
	const int		sizeY;

	SDL(const std::string& windowName, const Rect& screen);
	~SDL(void);

public:
	SDL_Renderer*	GetRenderer(void);
	SDL_Window*		GetWindow(void);
	int				GetScreenX(void){ return sizeX; }
	int				GetScreenY(void){ return sizeY; }
			
	static void Init(const std::string& windowName, const Rect& screen);
	static SDL& Instance(void);
};

inline void SDL::Init(const std::string& windowName, const Rect& screen){
	if (instance == nullptr){
		instance = new SDL(windowName, screen);
		atexit([](){delete instance; });
	}
}

inline SDL& SDL::Instance(void){
	if (instance == nullptr)
		Init();
	return *instance;
}

inline SDL_Renderer* SDL::GetRenderer(void){
	if (instance == nullptr)
		Init();
	return instance->renderer;
}

inline SDL_Window* SDL::GetWindow(void){
	if (instance == nullptr)
		Init();
	return instance->window;
}
