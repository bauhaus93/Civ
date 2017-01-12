#pragma once

#include <string>
#include <sstream>
#include <memory>
#include <queue>

#ifdef _WIN32
#include <SDL/SDL.h>
#endif
#ifdef __linux__
#include <SDL/SDL.h>
#endif

#include "Common.h"
#include "SDLException.h"
#include "Rect.h"
#include "Color.h"
#include "Log.h"
#include "Event.h"

#ifdef _WIN32
#undef main
#endif

class SDLEngine{

	static SDLEngine* instance;


	SDL_Window		*window;
	SDL_Renderer	*renderer;
	const int		sizeX;
	const int		sizeY;

	SDLEngine(const Rect& screen, std::string& windowName);
	~SDLEngine(void);

public:
	SDL_Renderer*	GetRenderer(void);
	SDL_Window*		GetWindow(void);
	int				GetScreenX(void){ return sizeX; }
	int				GetScreenY(void){ return sizeY; }

	void			DrawRect(const Rect& rect);
	void			DrawFillRect(const Rect & rect);
	void			DrawLine(int startX, int startY, int stopX, int stopY);
	RGBAColor		SetColor(const RGBAColor& col);

	void			ClearRenderTarget();
	void			ClearScene(void);

	void			ShowScene();

	void			SetWindowTitle(const std::string& title);
	std::queue<Event> PollEvents(void);

	static				void Start(const Rect& screen, std::string& windowName);
	static				void Stop();
	static SDLEngine&	Instance(void);

};

inline SDL_Renderer* SDLEngine::GetRenderer(void){
	return renderer;
}

inline SDL_Window* SDLEngine::GetWindow(void){
	return window;
}

inline SDLEngine& SDLEngine::Instance(void){
	return *instance;
}
