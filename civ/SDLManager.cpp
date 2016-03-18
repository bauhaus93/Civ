#include "SDLManager.h"

using namespace std;

SDL* SDL::instance = nullptr;

SDL::SDL(const string& windowName, int x, int y, int width, int height):
	sizeX{ width },
	sizeY{ height }{

	atexit(SDL::Release);

	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		throw SDLException("SDL_Init");
	}
	common::Log("SDL initialized!");

	window = SDL_CreateWindow(windowName.c_str(), x, y, width, height, SDL_WINDOW_SHOWN);
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


