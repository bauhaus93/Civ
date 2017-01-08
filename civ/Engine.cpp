#include "Engine.h"

Engine* Engine::instance = nullptr;

Engine::~Engine(){
}

void Engine::Stop(){
	if (instance != nullptr)
		delete instance;
	instance = nullptr;
}


