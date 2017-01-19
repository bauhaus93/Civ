#include "GameException.h"

using namespace std;


GameException::GameException(const std::string& errorType, const std::string& task, const std::string& description){
	stringstream s;
	s << errorType << " @ " << task << ": " << description;
	msg = s.str();
}


