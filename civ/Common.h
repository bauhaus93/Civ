#pragma once

#include <iostream>
#include <string>
#include <exception>

namespace common{

	void Log(const std::string& msg);
	void Log(const std::exception& e);
	void Log(const std::exception& e, const std::string exceptionName);
	void Log(const std::exception & e, const std::string exceptionName, const char* file, int line);

};
