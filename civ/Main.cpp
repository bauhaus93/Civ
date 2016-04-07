
#include <iostream>
#include <fstream>
#include <string>
#include <memory>

#ifdef _WIN32
#include <sdl\SDL.h>
#undef main
#endif

#ifdef __linux__
#include <SDL2/SDL.h>
#endif

#include "SDLManager.h"
#include "Game.h"

using namespace std;

int main(int argc, char **argv){
	unique_ptr<Game> game = nullptr;

	common::Seed();

	try{
		SDL::Init("Civ", 50, 50, 800, 600);
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
