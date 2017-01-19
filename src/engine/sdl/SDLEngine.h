#pragma once

#include <string>
#include <sstream>
#include <memory>
#include <queue>

#ifdef _WIN32
#include <SDL/SDL.h>
#endif
#ifdef __linux__
#include <SDL2/SDL.h>
#endif

#include "common/Common.h"
#include "SDLException.h"
#include "common/Rect.h"
#include "common/Color.h"
#include "Log.h"
#include "event/Event.h"
#include "event/Key.h"

class SDLEngine{

	static SDLEngine* instance;


	SDL_Window		*window;
	SDL_Renderer	*renderer;
	const int		sizeX;
	const int		sizeY;

	SDLEngine(const Rect& screen, const std::string& windowName);
	~SDLEngine();

public:
	SDL_Renderer*	GetRenderer();
	SDL_Window*		GetWindow();
	int				GetScreenX(){ return sizeX; }
	int				GetScreenY(){ return sizeY; }

	void			DrawRect(const Rect& rect);
	void			DrawFillRect(const Rect & rect);
	void			DrawLine(int startX, int startY, int stopX, int stopY);
	RGBAColor		SetColor(const RGBAColor& col);

	void			ClearRenderTarget();
	void			ClearScene();

	void			ShowScene();

	void			SetWindowTitle(const std::string& title);
	std::queue<Event> PollEvents();

	static				void Start(const Rect& screen, const std::string& windowName);
	static				void Stop();
	static SDLEngine&	Instance();

};

inline SDL_Renderer* SDLEngine::GetRenderer(){
	return renderer;
}

inline SDL_Window* SDLEngine::GetWindow(){
	return window;
}

inline SDLEngine& SDLEngine::Instance(){
	return *instance;
}
