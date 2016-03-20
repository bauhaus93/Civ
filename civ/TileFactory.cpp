#include "TileFactory.h"

using namespace std;

TileFactory::TileFactory(){
}

void TileFactory::AddTileset(unique_ptr<Tileset> tileset){
	tilesets.insert(make_pair(tileset->GetName(), move(tileset)));
}


unique_ptr<BaseTile> TileFactory::GetRandom(){
	auto& floor = tilesets.at("desert")->GetRandomFloor();
	return make_unique<BaseTile>(floor);
}
