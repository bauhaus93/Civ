#include "Game.h"

#include <chrono>

using namespace std;

Game::Game(void) :
	map{ Rect{0, 0, Engine::Instance().GetScreenX(), Engine::Instance().GetScreenY() } },
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
			Logger::Write(e);
			return 0;
		}
	}
	return 0;
}

void Game::Tick(void){

	HandleEvents();

	Render();

	if (ticks % fpsCheckInterval == 0){
		fps.Align(fpsCheckInterval);
		stringstream s;
		s << "fps: " << fps.GetFPS() << " | render time: " << lastRenderTime << " ms | delay: " << fps.GetDelay() << " ms " << endl;
		Engine::Instance().SetWindowTitle(s.str());
	}

	fps.Delay();
	ticks++;
}

void Game::HandleEvents(void){
	auto q = Engine::Instance().PollEvents();

	while (!q.empty()){
		Event& e = q.back();

		switch (e.type){
			case EventType::QUIT:
				throw CivException("Tick", "Quit was invoked");
				break;
			case EventType::KEY_PRESSED:
				if (e.key == Key::Q)
					throw CivException("Tick", "Q pressed");
				break;
			case EventType::MOUSE_PRESSED:
				MouseEvent(e);
				break;
			default:
				Logger::Write("Received unhandled event");
				break;
		}
		q.pop();
	}
}

void Game::MouseEvent(Event& e){
	if (e.mouse.button == MouseButton::LEFT)	//= left mouse click
		map.Clicked(e.mouse.pos.x, e.mouse.pos.y);
}

void Game::Render(void){
	auto start = common::Time();

	Engine::Instance().SetColor(RGBAColor{ 0, 0, 0, 0xFF });
	Engine::Instance().ClearScene();
	map.Render();
	Engine::Instance().ShowScene();

	lastRenderTime = common::TimeDiff(start);
}
