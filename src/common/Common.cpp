#include "Common.h"

using namespace std;



namespace common{

	mt19937 generator{};
	uniform_int_distribution<> distributionStd{};
	uniform_int_distribution<> distribution100{ 0, 99 };
	std::chrono::steady_clock timer{};
};
