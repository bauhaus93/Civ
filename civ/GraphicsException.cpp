#include "GraphicsException.h"


GraphicsException::GraphicsException(const std::string& task, const std::string& msg) :
	GameException("Graphics Exception", task, msg){
}
