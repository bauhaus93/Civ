#include "SDLManager.h"

using namespace std;

SDL* SDL::instance = nullptr;

SDL::SDL(const string& windowName, const Rect& screen):
	sizeX{ screen.w },
	sizeY{ screen.h }{

	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		throw SDLException("SDL_Init");
	}
	common::Log("SDL initialized!");

	window = SDL_CreateWindow(windowName.c_str(), screen.x, screen.y, screen.w, screen.h, SDL_WINDOW_SHOWN);
	if (window == nullptr)
		throw SDLException("SDL_CreateWindow");

	common::Log("Window created!");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | /*SDL_RENDERER_PRESENTVSYNC |*/ SDL_RENDERER_TARGETTEXTURE);
	if (renderer == nullptr)
		throw SDLException("SDL_CreateRenderer");

	if (SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND) == -1)
		throw SDLException("SDL_SetRenderDrawBlendMode");

		common::Log("Renderer created!");
}

SDL::~SDL(void){
	if (renderer != nullptr){
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
		common::Log("Renderer destroyed!");
	}

	if (window != nullptr){
		SDL_DestroyWindow(window);
		window = nullptr;
		common::Log("Window destroyed!");
	}

	SDL_Quit();
	common::Log("SDL quit!");
}

void SDL::DrawLine(int startX, int startY, int stopX, int stopY){

	if (SDL_RenderDrawLine(renderer, startX, startY, stopX, stopY) < 0)
		throw SDLException("SDL_RenderDrawLine");
}

void SDL::DrawRect(const Rect& rect){
	const SDL_Rect sdlRect{ rect.x, rect.y, rect.w, rect.h };

	if (SDL_RenderDrawRect(renderer, &sdlRect) < 0)
		throw SDLException("SDL_RenderDrawRect");
}

void SDL::DrawFillRect(const Rect& rect){
	const SDL_Rect sdlRect{ rect.x, rect.y, rect.w, rect.h };

	if (SDL_RenderFillRect(renderer, &sdlRect) < 0)
		throw SDLException("SDL_RenderDrawRect");
}

RGBAColor SDL::SetColor(const RGBAColor& col){
	RGBAColor old{ 0, 0, 0, 0 };

	if (SDL_GetRenderDrawColor(renderer, &old.r, &old.g, &old.b, &old.a) < 0)
		throw SDLException("SDL_GetRenderDrawColor");
	if (SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a) < 0)
		throw SDLException("SDL_SetRenderDrawColor");
	return std::move(old);
}



void SDL::ClearRenderTarget(void){
	if (SDL_SetRenderTarget(renderer, nullptr) == -1)
		throw SDLException("SDL_SetRenderTarget");
}

void SDL::ClearScene(){
	if (SDL_RenderClear(renderer) < 0)
		throw SDLException("SDL_RenderClear");
}

void SDL::ShowScene(){
	SDL_RenderPresent(renderer);
}

