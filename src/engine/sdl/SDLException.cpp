#include "SDLException.h"


SDLException::SDLException(const std::string& task) :
	GameException("SDL Exception", task, SDL_GetError()){
}
