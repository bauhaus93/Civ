#include "Map.h"

using namespace std;

Map::Map(void){

	spriteFactory.AddImage("bmp/TERRAIN1.bmp", "terrain1");
	spriteFactory.AddImage("bmp/TERRAIN2.bmp", "terrain2");
	spriteFactory.AddTransparent(0x87, 0x87, 0x87);
	spriteFactory.AddTransparent(0xFF, 0x00, 0xFF);
	
	LoadTilesets();

	grid.Create(64, 64);

	GridTraversal g{ grid };

	while (g.HasNext()){
		auto node = g.Next();
		node->SetTile(move(tileset.at(static_cast<TileType>(common::Random(0, 6)))->CreateTile()));
	}

}


Map::~Map(void){

}

void Map::LoadTilesets(){
	int x = 1, y = 1;

	auto ts = make_unique<TilesetSimple>("desert", 0, 10);
	ts->AddFloor(spriteFactory.CreateDiamondSprite("terrain1", x, y));
	x += 65;
	ts->AddFloor(spriteFactory.CreateDiamondSprite("terrain1", x, y));
	x += 65;
	ts->AddResource(spriteFactory.CreateDiamondSprite("terrain1", x, y));
	x += 65;
	ts->AddResource(spriteFactory.CreateDiamondSprite("terrain1", x, y));
	tileset.insert(make_pair(0, move(ts)));

	x = 1;
	y += 33;
	ts = make_unique<TilesetSimple>("prairie", 1, 10);
	ts->AddFloor(spriteFactory.CreateDiamondSprite("terrain1", x, y));
	x += 65*2;
	ts->AddResource(spriteFactory.CreateDiamondSprite("terrain1", x, y));
	x += 65;
	ts->AddResource(spriteFactory.CreateDiamondSprite("terrain1", x, y));
	tileset.insert(make_pair(1, move(ts)));

	x = 1;
	y += 33;
	ts = make_unique<TilesetSimple>("grasslands", 2, 10);
	ts->AddFloor(spriteFactory.CreateDiamondSprite("terrain1", x, y));
	ts->AddResource(spriteFactory.CreateDiamondSprite("terrain1", 456, 232));
	tileset.insert(make_pair(2, move(ts)));

	x = 1;
	y += 33*4;
	ts = make_unique<TilesetSimple>("tundra", 3, 10);
	ts->AddFloor(spriteFactory.CreateDiamondSprite("terrain1", x, y));
	x += 65 * 2;
	ts->AddResource(spriteFactory.CreateDiamondSprite("terrain1", x, y));
	x += 65;
	ts->AddResource(spriteFactory.CreateDiamondSprite("terrain1", x, y));
	tileset.insert(make_pair(3, move(ts)));

	x = 1;
	y += 33;
	ts = make_unique<TilesetSimple>("arctic", 4, 10);
	ts->AddFloor(spriteFactory.CreateDiamondSprite("terrain1", x, y));
	x += 65 * 2;
	ts->AddResource(spriteFactory.CreateDiamondSprite("terrain1", x, y));
	x += 65;
	ts->AddResource(spriteFactory.CreateDiamondSprite("terrain1", x, y));
	tileset.insert(make_pair(4, move(ts)));

	x = 1;
	y += 33;
	ts = make_unique<TilesetSimple>("swamp", 5, 10);
	ts->AddFloor(spriteFactory.CreateDiamondSprite("terrain1", x, y));
	x += 65 * 2;
	ts->AddResource(spriteFactory.CreateDiamondSprite("terrain1", x, y));
	x += 65;
	ts->AddResource(spriteFactory.CreateDiamondSprite("terrain1", x, y));
	tileset.insert(make_pair(5, move(ts)));

	x = 1;
	y += 33;
	ts = make_unique<TilesetSimple>("jungle", 6, 10);
	ts->AddFloor(spriteFactory.CreateDiamondSprite("terrain1", x, y));
	x += 65;
	ts->AddFloor(spriteFactory.CreateDiamondSprite("terrain1", x, y));
	x += 65;
	ts->AddResource(spriteFactory.CreateDiamondSprite("terrain1", x, y));
	x += 65;
	ts->AddResource(spriteFactory.CreateDiamondSprite("terrain1", x, y));
	tileset.insert(make_pair(6, move(ts)));

}



void Map::Render(void){
	grid.Render(1024, 768);
}
