
#include "Log.h"
#include "Game.h"
#include "Engine.h"
#include "AllegroEngine.h"

using namespace std;

#ifdef _WIN32
#undef main
#endif

int main(int argc, char **argv){
	Log::CreateStd();
	AllegroEngine::Start(1024, 768);
	


	Engine::Stop();
	Log::CloseStd();
}
