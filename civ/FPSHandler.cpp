#include "FPSHandler.h"

FPSHandler::FPSHandler(uint32_t desiredFPS_):
	desiredFPS{ desiredFPS_ },
	delay{ 25 }{

}

FPSHandler::~FPSHandler(void){
}

void FPSHandler::Align(uint32_t ticks){
	timepoint now = clock.now();
	duration diff = now - lastTime;
	lastFPS = ticks / diff.count();

	if (lastFPS > 1.05 * desiredFPS)
		delay *= 1.1;
	else if (lastFPS < 0.95 * desiredFPS)
		delay *= 0.9;

	lastTime = now;
}