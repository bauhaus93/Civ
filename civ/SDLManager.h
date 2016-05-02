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
#include "Definitions.h"

class SDL{

	static SDL*	instance;



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

	void		DrawRect(const Rect& rect);
	void		DrawFillRect(const Rect & rect);
	void		DrawLine(int startX, int startY, int stopX, int stopY);
	RGBAColor	SetColor(const RGBAColor& col);

	void		ClearRenderTarget();
	void		ClearScene(void);

	void		ShowScene();
	
	static void Init(const std::string& windowName, const Rect& screen);
	static void Init(void);

	static SDL& Instance(void);
};

inline void SDL::Init(const std::string& windowName, const Rect& screen){
	if (instance == nullptr){
		instance = new SDL(windowName, screen);
		atexit([](){delete instance; });
	}
}

inline void SDL::Init(void){
	Init("LEL", Rect{ 0, 0, 1024, 768 });
};

inline SDL& SDL::Instance(void){
	if (instance == nullptr)
		Init();
	return *instance;
}

inline SDL_Renderer* SDL::GetRenderer(void){
	return renderer;
}

inline SDL_Window* SDL::GetWindow(void){
	return window;
}
