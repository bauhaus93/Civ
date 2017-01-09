#include "AllegroEngine.h"

using namespace std;

AllegroEngine* AllegroEngine::instance = nullptr;

AllegroEngine::AllegroEngine(const Rect& screen, string& windowName){

	if (!al_install_system(ALLEGRO_VERSION_INT, nullptr))
		throw AllegroException("al_install_system");
	
	if (!al_install_keyboard())
		throw AllegroException("al_install_keyboard");
	
	if (!al_install_mouse())
		throw AllegroException("al_install_mouse");

	Logger::Write("Allegro initalized");

	display = al_create_display(screen.w, screen.h);
	if (display == nullptr)
		throw AllegroException("al_create_display");
	Logger::Write("Display initalized");

}

AllegroEngine::~AllegroEngine(void){
	if (display != nullptr){
		al_destroy_display(display);
		Logger::Write("Display destroyed");
	}

	al_uninstall_mouse();
	al_uninstall_keyboard();
	al_uninstall_system();
	Logger::Write("Allegro shut down");
}

void AllegroEngine::Start(const Rect& screen, string& windowName){
	if (instance == nullptr)
		instance = new AllegroEngine(screen, windowName);
	else
		throw CivException("AllegroEngine::Start", "Engine already started!");
}

void AllegroEngine::Stop(){
	if (instance != nullptr)
		delete instance;
	instance = nullptr;
}