#include "Game.h"

using namespace std;

Game::Game() :
	map{ make_unique<Map>(Rect{0, 0, Engine::Instance().GetScreenX(), Engine::Instance().GetScreenY() }) },
	fps{ 30 },
	ticks{ 0 },
	fpsCheckInterval{ 20 },
	lastRenderTime{ 0 }{
}

Game::~Game(){

}

int Game::Mainloop(){
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

void Game::Tick(){

	HandleEvents();
	Render();
	HandleFPS();
	ticks++;
}

void Game::HandleFPS(){
	if (ticks % fpsCheckInterval == 0){
		fps.Align(fpsCheckInterval);
		stringstream s;
		s << "fps: " << fps.GetFPS() << " | render time: " << lastRenderTime << " ms | delay: " << fps.GetDelay() << " ms";
		Engine::Instance().SetWindowTitle(s.str());
	}
	fps.Delay();
}

void Game::HandleEvents(){
	auto q = Engine::Instance().PollEvents();

	while (!q.empty()){
		Event& e = q.back();

		switch (e.type){
			case EventType::QUIT:
				throw CivException("Tick", "Quit was invoked");
				break;
			case EventType::KEY_PRESSED:
				switch(e.key){
				case Key::Q:
					throw CivException("Tick", "Q pressed");
				case Key::G:
					map = make_unique<Map>(Rect{0, 0, Engine::Instance().GetScreenX(), Engine::Instance().GetScreenY() });
					break;
				default:
					Logger::Write("Unhandled Key pressed");
					break;
				}
				break;
			case EventType::MOUSE_PRESSED:
				HandleMouseEvent(e);
				break;
			default:
				Logger::Write("Received unhandled event");
				break;
		}
		q.pop();
	}
}

void Game::HandleMouseEvent(Event& e){
	if (e.mouse.button == MouseButton::LEFT)
		map->Clicked(e.mouse.pos.x, e.mouse.pos.y);
}

void Game::Render(){
	auto start = common::Time();

	Engine::Instance().SetColor(RGBAColor{ 0, 0, 0, 0xFF });
	Engine::Instance().ClearScene();
	map->Render();
	Engine::Instance().ShowScene();

	lastRenderTime = common::TimeDiff(start);
}
