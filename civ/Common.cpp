#include "Common.h"

using namespace std;

namespace common{

	void Log(const string& msg){
		cout << msg << endl;
	}

	void Log(const exception& e){
		cout << e.what() << endl;
	}

};
