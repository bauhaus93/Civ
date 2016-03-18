#pragma once

#include <chrono>

#ifdef _WIN32
	#include <sdl\SDL.h>
#endif
#ifdef __linux__
	#include <SDL2/SDL.h>
#endif

typedef std::chrono::time_point<std::chrono::steady_clock> timepoint;
typedef std::chrono::duration<double> duration;

class FPSHandler{

	std::chrono::steady_clock	clock;

	uint32_t					desiredFPS;
	double						lastFPS;
	timepoint					lastTime;
	uint32_t					delay;

public:
								FPSHandler(uint32_t desiredFPS_);
								~FPSHandler(void);
	void						Align(uint32_t ticks);
	void						Delay(void);
	uint32_t					GetFPS(void) const { return static_cast<uint32_t>(lastFPS); };
	uint32_t					GetDelay(void) const { return delay; };
};

inline void FPSHandler::Delay(void){
	SDL_Delay(delay);
}

