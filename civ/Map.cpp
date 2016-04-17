#include "Map.h"

using namespace std;

Map::Map(const Rect& field) :
	drawField{ field.x, field.y, field.w, field.h }{

	spriteFactory.AddImage("bmp/TERRAIN1.bmp", "terrain1");
	spriteFactory.AddImage("bmp/TERRAIN2.bmp", "terrain2");
	spriteFactory.AddTransparent(0x87, 0x87, 0x87);
	spriteFactory.AddTransparent(0xFF, 0x00, 0xFF);

	mouseClickComparator = spriteFactory.CreateDiamondSprite("terrain1", 66, 447);
	RGBAColor col = mouseClickComparator->PixelAt(0, 0);
	cout << "lelele" << (int)col.r << ", " << (int)col.g << ", " << (int)col.b << ", " << (int)col.a << endl;

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

void Map::AlignViewPos(int x, int y){
	x -= drawField.x;
	y -= drawField.y;

	RGBAColor col = mouseClickComparator->PixelAt(63, 31);
	cout << (int)col.r << ", " << (int)col.g << ", " << (int)col.b << ", " << (int)col.a << endl;

	//cout << "square: " << (x / 64) << ", " << (y / 32) << endl;

	if (x >= 0 && x < drawField.w && y >= 0 && y < drawField.h){
		RGBAColor col = mouseClickComparator->PixelAt(x % 64, y % 32);
		int relX = x / 64;
		int relY = 2*(y / 32);
		
		switch (col.r){ 
			case 107:
				relX--;
				relY--;
				break;
			case 159:
				relY--;
				break;
			case 71:
				relY++;
				break;
			case 167:
				relX--;
				relY++;
			case 27:
				break;
			default:
				cout << "DEFAULT SHOULD NOT HAPPEN LEL: " << (int)col.r << ", " << (int)col.g << ", " << (int)col.b << ", " << (int)col.a << endl;
				break;
		}

		//cout << "square: " << (x % 64) << ", " << (y % 32) << endl;
		
		//cout << (int)col.r << ", " << (int)col.g << ", " << (int)col.b << ", " << (int)col.a << endl;
		
		grid.MoveView(relX, relY);
	}
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
	x += 65 * 2;
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
	y += 33 * 4;
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
	grid.Render(drawField);
	//mouseClickComparator->Render(0, 0);
}
