
#include "Log.h"
#include "Game.h"
#include "Engine.h"
#include "Rect.h"

using namespace std;



int main(int argc, char **argv){
	Log::CreateStd();
	Engine::Start(Rect{ 50, 50, 1024, 768 }, string("test"));

	Game game{};

	game.Mainloop();
}
