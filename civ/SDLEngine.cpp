#include "SDLEngine.h"

using namespace std;

SDLEngine* SDLEngine::instance = nullptr;

SDLEngine::SDLEngine(const Rect& screen, string& windowName):
	sizeX{ screen.w },
	sizeY{ screen.h }{

	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		throw SDLException("SDL_Init");
	}
	Logger::Write("SDL initialized!");

	window = SDL_CreateWindow(windowName.c_str(), screen.x, screen.y, screen.w, screen.h, SDL_WINDOW_SHOWN);
	if (window == nullptr)
		throw SDLException("SDL_CreateWindow");

	Logger::Write("Window created!");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | /*SDL_RENDERER_PRESENTVSYNC |*/ SDL_RENDERER_TARGETTEXTURE);
	if (renderer == nullptr)
		throw SDLException("SDL_CreateRenderer");

	if (SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND) == -1)
		throw SDLException("SDL_SetRenderDrawBlendMode");

	Logger::Write("Renderer created!");
}

SDLEngine::~SDLEngine(void){
	if (renderer != nullptr){
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
		Logger::Write("Renderer destroyed!");
	}

	if (window != nullptr){
		SDL_DestroyWindow(window);
		window = nullptr;
		Logger::Write("Window destroyed!");
	}

	SDL_Quit();
	Logger::Write("SDL quit!");
}

void SDLEngine::DrawLine(int startX, int startY, int stopX, int stopY){

	if (SDL_RenderDrawLine(renderer, startX, startY, stopX, stopY) < 0)
		throw SDLException("SDL_RenderDrawLine");
}

void SDLEngine::DrawRect(const Rect& rect){
	const SDL_Rect sdlRect{ rect.x, rect.y, rect.w, rect.h };

	if (SDL_RenderDrawRect(renderer, &sdlRect) < 0)
		throw SDLException("SDL_RenderDrawRect");
}

void SDLEngine::DrawFillRect(const Rect& rect){
	const SDL_Rect sdlRect{ rect.x, rect.y, rect.w, rect.h };

	if (SDL_RenderFillRect(renderer, &sdlRect) < 0)
		throw SDLException("SDL_RenderDrawRect");
}

RGBAColor SDLEngine::SetColor(const RGBAColor& col){
	RGBAColor old{ 0, 0, 0, 0 };

	if (SDL_GetRenderDrawColor(renderer, &old.r, &old.g, &old.b, &old.a) < 0)
		throw SDLException("SDL_GetRenderDrawColor");
	if (SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a) < 0)
		throw SDLException("SDL_SetRenderDrawColor");
	return std::move(old);
}

void SDLEngine::ClearRenderTarget(void){
	if (SDL_SetRenderTarget(renderer, nullptr) == -1)
		throw SDLException("SDL_SetRenderTarget");
}

void SDLEngine::ClearScene(){
	if (SDL_RenderClear(renderer) < 0)
		throw SDLException("SDL_RenderClear");
}

void SDLEngine::ShowScene(){
	SDL_RenderPresent(renderer);
}

void SDLEngine::Start(const Rect& screen, string& windowName){
	if (instance == nullptr)
		instance = new SDLEngine(screen, windowName);
	else
		throw CivException("SDLEngine::Start", "Engine already started!");
}

void SDLEngine::Stop(){
	if (instance != nullptr)
		delete instance;
	instance = nullptr;
}