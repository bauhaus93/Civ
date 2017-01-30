#pragma once

#include <chrono>
#include <thread>

typedef std::chrono::time_point<std::chrono::steady_clock> timepoint;
typedef std::chrono::duration<float> duration;

class FPSHandler{

	std::chrono::steady_clock	clock;
	timepoint					lastTime;

	double						desiredFPS;
	double						lastFPS;
	double						delay;

public:
	explicit					FPSHandler(uint32_t desiredFPS_);
								~FPSHandler();
	void						Align(uint32_t ticks);
	void						Delay();
	uint32_t					GetFPS() const { return static_cast<uint32_t>(lastFPS); };
	uint32_t					GetDelay() const { return static_cast<uint32_t>(delay); };
};

inline void FPSHandler::Delay(){
	std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(delay)));
}
