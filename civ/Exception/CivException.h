#pragma once

#include <string>

#include "GameException.h"

class CivException : public GameException{

public:
	CivException(const std::string& task, const std::string& description);
};



