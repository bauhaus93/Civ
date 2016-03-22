#include "Map.h"

using namespace std;

Map::Map(void){

	spriteFactory.AddImage("bmp/TERRAIN1.bmp", "terrain1");
	spriteFactory.AddImage("bmp/TERRAIN2.bmp", "terrain2");


	auto ts = make_unique<Tileset>("desert");
	auto s = spriteFactory.CreateDiamondSprite("terrain1", 1, 1, 0x00878787);
	if (s == nullptr)
		throw CivException("CreateDiamondSprite", "result was null");
	//sprite = move(s);

	ts->AddFloor(move(s));

	tileFactory.AddTileset(move(ts));
	
	tile = tileFactory.GetRandom();

}


Map::~Map(void){
}

void Map::Render(void){
	tile->Render(0, 0);
//	sprite->Render(0, 0);
}
