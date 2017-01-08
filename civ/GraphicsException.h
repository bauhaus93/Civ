#pragma once

#include <string>

#include "GameException.h"

class GraphicsException : public GameException{
public:
	GraphicsException(const std::string& task, const std::string& msg);
};

