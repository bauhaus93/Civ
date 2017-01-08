#include "AllegroException.h"

#include "CivExceptions.h"

AllegroException::AllegroException(const std::string & task):
GraphicsException(task, "allegro errno = " + std::to_string(al_get_errno())){
}

AllegroException::~AllegroException(){
}
