#pragma once

#include <chrono>

#ifdef _WIN32
	#include <sdl/SDL.h>
#endif
#ifdef __linux__
	#include <SDL2/SDL.h>
#endif

typedef std::chrono::time_point<std::chrono::steady_clock> timepoint;
typedef std::chrono::duration<float> duration;

class FPSHandler{

	std::chrono::steady_clock	clock;
	timepoint					lastTime;

	double						desiredFPS;
	double						lastFPS;
	double						delay;

public:
								FPSHandler(uint32_t desiredFPS_);
								~FPSHandler(void);
	void						Align(uint32_t ticks);
	void						Delay(void);
	uint32_t					GetFPS(void) const { return static_cast<uint32_t>(lastFPS); };
	uint32_t					GetDelay(void) const { return static_cast<uint32_t>(delay); };
};

inline void FPSHandler::Delay(void){
	SDL_Delay(static_cast<Uint32>(delay));
}

