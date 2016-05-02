
#include <memory>

#include "SDLManager.h"
#include "Game.h"

using namespace std;

#ifdef _WIN32
#undef main
#endif

int main(int argc, char **argv){
	unique_ptr<Game> game = nullptr;

	common::Seed();

	try{
		SDL::Init("Civ", Rect{ 50, 50, 1024, 768 });
	}
	catch (const SDLException& e){
		common::Log(e);
		return 1;
	}

	try{
		game = make_unique<Game>();
	}
	catch (const GameException& e){
		common::Log(e);
		return 1;
	}

	return game->Mainloop();
}
