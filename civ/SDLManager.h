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

class SDL{
	
	static SDL*	instance;

	static void Init(void){ Init("LEL", 0, 0, 1024, 768); };

	SDL_Window		*window;
	SDL_Renderer	*renderer;
	const int		sizeX;
	const int		sizeY;

	SDL(const std::string& windowName, int x, int y, int width, int height);
	~SDL(void);

public:
	
	static void Init(const std::string& windowName, int x, int y, int width, int height);
	static void Release(void);
	static SDL& Instance(void);
	static SDL_Renderer* GetRenderer(void);
	static SDL_Window* GetWindow(void);
};

inline void SDL::Init(const std::string& windowName, int x, int y, int width, int height){
	if (instance == nullptr){
		instance = new SDL(windowName, x, y, width, height);
		atexit(SDL::Release);
	}
}

inline void SDL::Release(void){
	if (instance != nullptr){
		delete instance;
		instance = nullptr;
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
