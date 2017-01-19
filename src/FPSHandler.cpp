#include "FPSHandler.h"

FPSHandler::FPSHandler(uint32_t desiredFPS_):
	desiredFPS{ static_cast<double>(desiredFPS_) },
	delay{ 25 }{

}

FPSHandler::~FPSHandler(){
}

void FPSHandler::Align(uint32_t ticks){
	timepoint now = clock.now();
	duration diff = now - lastTime;
	lastFPS = ticks / diff.count();

	if (lastFPS > 1.05 * desiredFPS)
		delay *= 1.1f;
	else if (lastFPS < 0.95 * desiredFPS)
		delay *= 0.9f;

	lastTime = now;
}