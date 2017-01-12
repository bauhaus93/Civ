#include "AllegroException.h"


AllegroException::AllegroException(const std::string & task):
GameException("Allegro Exception", task, "allegro errno = " + std::to_string(al_get_errno())){
}

AllegroException::~AllegroException(){
}
