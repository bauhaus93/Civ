#include "Common.h"

using namespace std;

namespace common{

	void SDLError(const string& error){
		cerr << "[ERROR] " << error << ": " << SDL_GetError() << endl;
	}

	void Error(const string& error){
		cerr << "[ERROR] " << error << endl;
	}

	void Log(const string& msg){
		cout << msg << endl;
	}
};
