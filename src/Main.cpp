
#include <memory>
#include <string>
#include <iostream>
#include <random>

#include "Log.h"
#include "Game.h"
#include "engine/Engine.h"
#include "common/Rect.h"

#include "map/SimplexNoise.h"

using namespace std;



int main(int argc, char **argv){
	Log::CreateStd();
	Engine::Start(Rect{ 50, 50, 1024, 768 }, "test");

	mt19937 rng{random_device{}()};
	double roughness = 10.0;
	double scale = 0.005;
	double octaves = 4;

	while(true){
		Engine::Instance().ClearScene();
		SimplexNoise noise {};
		roughness *= 0.95;
		for(int i = 0; i < 1024/2; i++){
			for(int j = 0; j < 768/2; j++){
				double n = noise.GetOctavedNoise(i, j, 4, roughness, 0.005);

				n = (n + 1) / 2;
				if(n > 0.5)
					n = 1;
				else
					n = 0;
				Engine::Instance().SetColor(RGBAColor{0, 0xFF * n, 0xFF * (1-n), 0xFF});
				Engine::Instance().DrawFillRect(Rect{i*2, j*2, 2, 2});


			}
		}
		Engine::Instance().ShowScene();
		Engine::Instance().SetWindowTitle("octaves: " + to_string(octaves) + " | roughness: " + to_string(roughness) + " | scale: " + to_string(scale));
		auto q = Engine::Instance().PollEvents();

		while (!q.empty()){
			Event& e = q.back();
			if(e.type == EventType::QUIT)
				return 0;
			q.pop();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(750)));

	}

	/*unique_ptr<Game> game = nullptr;

	Log::CreateStd();
	Engine::Start(Rect{ 50, 50, 1024, 768 }, "test");

	try{
		game = make_unique<Game>();
	}
	catch(const GameException& e){
		Logger::Write(e);
		return 1;
	}

	game->Mainloop();*/

	return 0;
}
