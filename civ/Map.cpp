#include "Map.h"

using namespace std;

Map::Map(void){

	spriteFactory.AddImage("bmp/TERRAIN1.bmp", "terrain1");
	spriteFactory.AddImage("bmp/TERRAIN2.bmp", "terrain2");
	spriteFactory.AddTransparent(0x87, 0x87, 0x87);
	spriteFactory.AddTransparent(0xFF, 0x00, 0xFF);
	
	LoadTilesets();
	tile = tileset.at(0)->CreateTile();
	tileset.at(0)->CreateTileSprite(*tile);

	grid.Create(64, 64);

	GridTraversal g{ grid };

	int i = 0;
	while (g.HasNext()){
		auto node = g.Next();
		node->SetTile(move(tileset.at(0)->CreateTile()));
	}

}


Map::~Map(void){

}

void Map::LoadTilesets(){

	auto ts = make_unique<TilesetSimple>("desert", 1, 50);

	ts->AddFloor(spriteFactory.CreateDiamondSprite("terrain1", 1, 1));
	ts->AddFloor(spriteFactory.CreateDiamondSprite("terrain1", 66, 1));
	ts->AddResource(spriteFactory.CreateDiamondSprite("terrain1", 131, 1));
	ts->AddResource(spriteFactory.CreateDiamondSprite("terrain1", 196, 1));

	tileset.insert(make_pair(0, move(ts)));
}



void Map::Render(void){
	grid.Render(1024, 768);
	//tile->Render(0, 0);
}
