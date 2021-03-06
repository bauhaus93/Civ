
#include <memory>

#include "Log.h"
#include "Game.h"
#include "engine/Engine.h"
#include "engine/SpriteManager.h"
#include "common/Rect.h"


using namespace std;

int main(int argc, char **argv){
	unique_ptr<Game> game = nullptr;

	Log::CreateStd();
	Engine::Start(Rect{ 50, 50, 1024, 768 }, "test");
	SpriteManager::Start();


	try{
		game = make_unique<Game>();
	}
	catch(const GameException& e){
		Logger::Write(e);
		return 1;
	}

	game->Mainloop();

	return 0;
}
