#pragma once

#include <iostream>
#include <string>
#include <exception>
#include <random>
#include <chrono>

namespace common{

	extern std::mt19937 generator;
	extern std::uniform_int_distribution<> distributionStd;
	extern std::uniform_int_distribution<> distribution100;
	extern std::chrono::high_resolution_clock timer;

	void Log(const std::string& msg);
	void Log(const std::exception& e);

	void Seed();
	void Seed(unsigned int seed);
	unsigned int Random();
	unsigned int Random(int range);
	int Random(int min, int max);

	std::chrono::time_point<std::chrono::steady_clock> Time();
	unsigned int TimeDiff(std::chrono::time_point<std::chrono::steady_clock> start);

};

inline void common::Seed(){
	std::random_device randomDevice;
	Seed(randomDevice());
}

inline void common::Seed(unsigned int seed){
	generator.seed(seed);
	std::cout << "seed = " << seed << std::endl;
}

inline unsigned int common::Random(){
	return static_cast<unsigned int>(distribution100(generator));
}

inline unsigned int common::Random(int range){
	return static_cast<unsigned int>(distributionStd(generator) % range);
}

inline int common::Random(int min, int max){
	return min + (distributionStd(generator) % (max - min + 1));
}

inline std::chrono::time_point<std::chrono::steady_clock> common::Time(){
	return timer.now();
}

inline unsigned int common::TimeDiff(std::chrono::time_point<std::chrono::steady_clock> start){
	return static_cast<unsigned int>((std::chrono::nanoseconds(timer.now() - start).count())*1e-6);

}
