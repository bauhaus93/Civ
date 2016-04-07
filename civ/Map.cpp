#include "Map.h"

using namespace std;

Map::Map(void){

	spriteFactory.AddImage("bmp/TERRAIN1.bmp", "terrain1");
	spriteFactory.AddImage("bmp/TERRAIN2.bmp", "terrain2");
	spriteFactory.AddTransparent(0x87, 0x87, 0x87);
	spriteFactory.AddTransparent(0xFF, 0x00, 0xFF);

	LoadTilesets();

	tile = make_unique<Tile>();

	tileset.at(TileType::DESERT)->CompleteTile(*tile);
	
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

	/*constexpr SpritePosition desert[] = {	{0, 0, 1, 1},
											{0, 1, 65, 0},
											{1, 1, 65, 0},
											{1, 1, 65, 0} };


	int x = 0, y = 0;

	auto ModOffset = [&x, &y](SpritePosition& pos){pos.offsetType == 0 ? (x = pos.offsetX, y = pos.offsetY) : (x += pos.offsetX, y += pos.offsetY); };
	auto AddByType = [this, &ts](SpritePosition& pos, int x, int y){pos.type == 0 ? (ts->AddFloor(this->spriteFactory.CreateDiamondSprite("terrain1", x, y))) : (ts->AddResource(this->spriteFactory.CreateDiamondSprite("terrain1", x, y))); };
	auto AddToTilesets = [this, &ts](TileType type){this->tileset.insert(make_pair(type, move(ts))); };
	
	for (auto pos : desert){
		ModOffset(pos);
		cout << x << "/" << y << endl;
		
		AddByType(pos, x, y);
	}
	AddToTilesets(TileType::DESERT);*/

}



void Map::Render(void){
	tile->Render(0, 0);
}

