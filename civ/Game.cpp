#include "Game.h"

#include <chrono>

using namespace std;

Game::Game(void) :
	map{ Rect{0, 0, SDL::Instance().GetScreenX(), SDL::Instance().GetScreenY() } },
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
				if (e.key.keysym.sym == SDLK_q)
					throw CivException("Tick", "Q pressed");
				break;
			case SDL_MOUSEBUTTONUP:
				MouseEvent(e);
				break;
			case SDL_WINDOWEVENT:
				WindowEvent(e);
				break;
			default:
				break;
		}
	}

	Render();

	if (ticks % fpsCheckInterval == 0){
		fps.Align(fpsCheckInterval);
		stringstream s;
		s << "fps: " << fps.GetFPS() << " | render time: " << lastRenderTime << " ms | delay: " << fps.GetDelay() << " ms " << endl;
		SDL_SetWindowTitle(SDL::Instance().GetWindow(), s.str().c_str());
	}

	fps.Delay();

	ticks++;
}

void Game::WindowEvent(SDL_Event& e){
	switch (e.window.event){
		case SDL_WINDOWEVENT_MINIMIZED:
			common::Log("MINIMIZED!");
			break;
		case SDL_WINDOWEVENT_RESTORED:
			common::Log("RESTORED!");
			break;
		default:
			break;
	}
}

void Game::MouseEvent(SDL_Event& e){
	if (e.button.button == SDL_BUTTON_LEFT)
		map.Clicked(e.button.x, e.button.y);
}

void Game::Render(void){
	auto start = common::Time();

	map.Render();
	SDL::Instance().ShowScene();

	lastRenderTime = common::TimeDiff(start);
}

