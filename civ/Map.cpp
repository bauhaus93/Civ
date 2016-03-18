#include "Map.h"



Map::Map(void){
	spriteFactory.AddImage("bmp/TERRAIN1.bmp", "terrain1");
	spriteFactory.AddImage("bmp/TERRAIN2.bmp", "terrain2");
	sprite = spriteFactory.CreateDiamondSprite("terrain1", 1, 1, 0x00878787);
}


Map::~Map(void){
}

void Map::Render(void){
	sprite->Render(0, 0);
}
