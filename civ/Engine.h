#pragma once

#include "Definitions.h"

class Engine{

protected:

	static Engine* Engine::instance;
	virtual ~Engine() = 0;
public:

	static void		Stop();
	static Engine&	Instance(void);

};

inline Engine& Engine::Instance(void){
	return *instance;
}