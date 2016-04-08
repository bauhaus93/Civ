#include "Map.h"

using namespace std;

Map::Map(void){

	spriteFactory.AddImage("bmp/TERRAIN1.bmp", "terrain1");
	spriteFactory.AddImage("bmp/TERRAIN2.bmp", "terrain2");
	spriteFactory.AddTransparent(0x87, 0x87, 0x87);
	spriteFactory.AddTransparent(0xFF, 0x00, 0xFF);

	LoadTilesets();

	tile = make_unique<Tile>();

	tileset.at(0)->InitiateTile(*tile);
	tileset.at(0)->CreateTileSprite(*tile);
	
}


Map::~Map(void){
}

typedef struct{
	uint8_t type;
	uint8_t offsetType;
	int offsetX;
	int offsetY;
}SpritePosition;

void Map::LoadTilesets(){

	auto ts = make_unique<TilesetSimple>(50);

	constexpr SpritePosition desert[] = {	{0, 0, 1, 1},
											{0, 1, 65, 0},
											{1, 1, 65, 0},
											{1, 1, 65, 0} };

	ts->AddFloor(spriteFactory.CreateDiamondSprite("terrain1", 1, 1));
	ts->AddFloor(spriteFactory.CreateDiamondSprite("terrain1", 66, 1));
	ts->AddResource(spriteFactory.CreateDiamondSprite("terrain1", 131, 1));	
	ts->AddResource(spriteFactory.CreateDiamondSprite("terrain1", 196, 1));

	tileset.insert(make_pair(0, move(ts)));
}



void Map::Render(void){
	tile->Render(0, 0);
}

