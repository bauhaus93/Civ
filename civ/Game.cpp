#include "Game.h"

#include <chrono>

using namespace std;

Game::Game(void) :
	map{ Rect{0, 0, SDL::Instance().GetScreenX(), SDL::Instance().GetScreenY() } },
	fps{ 30 },
	renderer{ Renderer::Instance() },
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
				if (e.key.keysym.sym == SDLK_q)
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
		s << "fps: " << fps.GetFPS() << " | render time: " << lastRenderTime << " ms | delay: " << fps.GetDelay() << " ms" << endl;
		SDL_SetWindowTitle(SDL::Instance().GetWindow(), s.str().c_str());
	}

	fps.Delay();

	ticks++;
}

/* Render times:
	1 desert diamond: 2-6ms (mainly around 2)
*/

void Game::Render(void){
	auto start = common::Time();
	renderer.Clear();
	map.Render();
	renderer.Show();
	lastRenderTime = common::TimeDiff(start);
}

