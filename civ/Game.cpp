#include "Game.h"

#include <chrono>

using namespace std;

Game::Game(void):
	map{},
	fps{ 30 },
	ticks{ 0 },
	fpsCheckInterval{ 20 }{
}

Game::~Game(void){

}

int Game::Mainloop(void){
	while (true){
		try{
			Tick();
		}
		catch (const GameException& e){
			common::Log(e);
			return 0;
		}
	}
	return 0;
}

void Game::Tick(void){
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0){
		switch (e.type){
			case SDL_QUIT:
				throw CivException("Tick", "SDL_QUIT invoked");
				break;
			case SDL_KEYUP:
				if(e.key.keysym.sym == SDLK_q)
					throw CivException("Tick", "Q pressed");
				break;
			default:
				break;
		}
		//TODO: Process Events
	}

	Render();

	if (ticks % fpsCheckInterval == 0){
		fps.Align(fpsCheckInterval);
		stringstream s;
		s << "fps: " << fps.GetFPS() << " | delay: " << fps.GetDelay() << " ms" << endl;
		SDL_SetWindowTitle(SDL::GetWindow(), s.str().c_str());
	}

	fps.Delay();

	ticks++;
}

/* Render times:
	1 desert diamond: 2-6ms (mainly around 2)
*/

void Game::Render(void){
	SDL_RenderClear(SDL::GetRenderer());
	map.Render();
	SDL_RenderPresent(SDL::GetRenderer());
}

