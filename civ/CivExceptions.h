#pragma once

#include <exception>
#include <string>
#include <sstream>

#include <sdl\SDL.h>

class GameException : public std::exception{

	std::string msg;

public:
						GameException(const std::string& errorType, const std::string& task, const std::string& description);
	virtual const char* what() const throw(){ return msg.c_str(); };
};

class CivException : public GameException{

public:
	CivException(const std::string& task, const std::string& description);
};

class SDLException : public GameException{

public:
	SDLException(const std::string& task);
};