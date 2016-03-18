#include "CivExceptions.h"

using namespace std;

SDLException::SDLException(const string& task):
	GameException("SDL Exception", task, SDL_GetError()){
}

CivException::CivException(const string& task, const string& description):
	GameException("Civ Exception", task, description){
}


GameException::GameException(const std::string& errorType, const std::string& task, const std::string& description){
	stringstream s;
	s << errorType << " @ " << task << ": " << description;
	msg = s.str();
}


