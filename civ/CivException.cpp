#include "CivException.h"

CivException::CivException(const std::string& task, const std::string& description) :
	GameException("Civ Exception", task, description){
}