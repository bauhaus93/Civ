#include "Common.h"

using namespace std;



namespace common{

	mt19937 generator{};
	uniform_int_distribution<> distributionStd{};
	uniform_int_distribution<> distribution100{ 0, 99 };
	std::chrono::steady_clock timer{};

	void Log(const string& msg){
		cout << msg << endl;
	}

	void Log(const exception& e){
		cout << e.what() << endl;
	}

};
