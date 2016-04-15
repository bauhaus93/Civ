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
			case SDL_MOUSEBUTTONUP:
				MouseEvent(e);
				break;
			case SDL_WINDOWEVENT:
				WindowEvent(e);
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
		map.AlignViewPos(e.button.x, e.button.y);

}

/* Render times:
	1 desert diamond: 2-6ms (mainly around 2)
*/

void Game::Render(void){
	auto start = common::Time();

	//Render on temporary Sprite
	Sprite s{ Rect{0, 0, map.GetDrawField().w, map.GetDrawField().h} };
	renderer.SetTarget(s);
	map.Render();

	//renderer.Show();	MAYBE NEEDED

	//Draw Sprite on Screen
	renderer.SetStdTarget();
	renderer.Clear();
	s.Render(0, 0);

	renderer.SetColor(RGBAColor{ 0xFF, 0, 0, 0xFF });
	for (int y = 0; y < map.GetDrawField().h; y += 32)
		for (int x = 0; x < map.GetDrawField().w; x += 64)
			renderer.DrawRect(Rect{ x, y, 64, 32 });

	renderer.Show();

	lastRenderTime = common::TimeDiff(start);
}

