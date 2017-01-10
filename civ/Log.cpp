#include "Log.h"

using namespace std;

Log* Log::instance = nullptr;

Log::Log(string& name):
	file{ name },
	out{ file }{
}

Log::Log():
	out{ cerr }{
}


Log::~Log(){
	if (file.is_open())
		file.close();
}

void Log::CreateStd(string& name){
	if (instance == nullptr){
		instance = new Log(name);
		atexit([](){CloseStd(); });
	}
	else
		throw CivException("Log::CreateStd", "Standard-Log already existing!");
}

void Log::CreateStd(){
	if (instance == nullptr)
		instance = new Log();
	else
		throw CivException("Log::CreateStd", "Standard-Log already existing!");
}

void Log::CloseStd(){
	if (instance != nullptr)
		delete instance;
}

//TODO implement time safely
void Log::Write(const string& msg){
	//time_t t = chrono::system_clock::to_time_t(chrono::system_clock::now());
	//out << "[" << put_time(localtime(&t), "%H:%M:%S") << "]" << msg << endl;

	out << msg << endl;
}

void Log::Write(const exception& e){
	Write(e.what());
}

Log& Log::Instance(void){
	return *instance;
}

void Logger::Write(const string& msg){
	Log::Instance().Write(msg);
}

void Logger::Write(const exception & e){
	Log::Instance().Write(e);
}
