#include "Map.h"

using namespace std;

Map::Map(const Rect& drawField_) :
	drawField{ drawField_ },
	grid{}{

	spriteFactory.AddImage("bmp/TERRAIN1.bmp", "terrain1");
	spriteFactory.AddImage("bmp/TERRAIN2.bmp", "terrain2");
	spriteFactory.AddTransparent(0x87, 0x87, 0x87);
	spriteFactory.AddTransparent(0xFF, 0x00, 0xFF);

	LoadTilesets();

	
	grid.SetMouseClickComparator(spriteFactory.CreateDiamondSprite("terrain1", 66, 447));
	grid.Create(75, 120);
	grid.AlignViewToCenter(drawField.w, drawField.h);

	GridTraversal g{ grid };

	while (g.HasNext()){
		auto node = g.Next();
		node->SetTile(make_unique<Tile>(tileset.at(common::Random(tileset.size()))));
	}
	change = true;
	
}


Map::~Map(void){

}

void Map::Clicked(int screenX, int screenY){
	screenX -= drawField.x;
	screenY -= drawField.y;

	if (screenX >= 0 && screenX < drawField.w && screenY >= 0 && screenY < drawField.h){
		grid.CenterToClick(screenX, screenY, drawField.w, drawField.h);
	}
	change = true;
}

void Map::LoadTilesets(void){
	int x = 1, y = 1;

	tileset.push_back(Tileset("desert", RESOURCE_CHANCE));
	tileset.back().AddFloor(spriteFactory.CreateDiamondSprite("terrain1", x, y));
	x += 65;
	tileset.back().AddFloor(spriteFactory.CreateDiamondSprite("terrain1", x, y));
	x += 65;
	tileset.back().AddResource(Resource{ spriteFactory.CreateDiamondSprite("terrain1", x, y) });
	x += 65;
	tileset.back().AddResource(Resource{ spriteFactory.CreateDiamondSprite("terrain1", x, y) });

	x = 1;
	y += 33;
	tileset.push_back(Tileset("prairie", RESOURCE_CHANCE));
	tileset.back().AddFloor(spriteFactory.CreateDiamondSprite("terrain1", x, y));
	x += 65 * 2;
	tileset.back().AddResource(Resource{ spriteFactory.CreateDiamondSprite("terrain1", x, y) });
	x += 65;
	tileset.back().AddResource(Resource{ spriteFactory.CreateDiamondSprite("terrain1", x, y) });

	
	x = 1;
	y += 33;
	tileset.push_back(Tileset("grasslands", RESOURCE_CHANCE));
	tileset.back().AddFloor(spriteFactory.CreateDiamondSprite("terrain1", x, y));
	tileset.back().AddResource(Resource(spriteFactory.CreateDiamondSprite("terrain1", 456, 232)));

	x = 1;
	y += 33 * 4;
	tileset.push_back(Tileset("tundra", RESOURCE_CHANCE));
	tileset.back().AddFloor(spriteFactory.CreateDiamondSprite("terrain1", x, y));
	x += 65 * 2;
	tileset.back().AddResource(Resource(spriteFactory.CreateDiamondSprite("terrain1", x, y)));
	x += 65;
	tileset.back().AddResource(Resource(spriteFactory.CreateDiamondSprite("terrain1", x, y)));

	x = 1;
	y += 33;
	tileset.push_back(Tileset("arctic", RESOURCE_CHANCE));
	tileset.back().AddFloor(spriteFactory.CreateDiamondSprite("terrain1", x, y));
	x += 65 * 2;
	tileset.back().AddResource(Resource(spriteFactory.CreateDiamondSprite("terrain1", x, y)));
	x += 65;
	tileset.back().AddResource(Resource(spriteFactory.CreateDiamondSprite("terrain1", x, y)));

	x = 1;
	y += 33;
	tileset.push_back(Tileset("swamp", RESOURCE_CHANCE));
	tileset.back().AddFloor(spriteFactory.CreateDiamondSprite("terrain1", x, y));
	x += 65 * 2;
	tileset.back().AddResource(Resource(spriteFactory.CreateDiamondSprite("terrain1", x, y)));
	x += 65;
	tileset.back().AddResource(Resource(spriteFactory.CreateDiamondSprite("terrain1", x, y)));

	x = 1;
	y += 33;
	tileset.push_back(Tileset("jungle", RESOURCE_CHANCE));
	tileset.back().AddFloor(spriteFactory.CreateDiamondSprite("terrain1", x, y));
	x += 65;
	tileset.back().AddFloor(spriteFactory.CreateDiamondSprite("terrain1", x, y));
	x += 65;
	tileset.back().AddResource(Resource(spriteFactory.CreateDiamondSprite("terrain1", x, y)));
	x += 65;
	tileset.back().AddResource(Resource(spriteFactory.CreateDiamondSprite("terrain1", x, y)));

}

void Map::Render(void){
	static Sprite s{ Rect{ 0, 0, drawField.w, drawField.h } };

	if (change){
		s.SetAsRenderTarget();
		SDL::Instance().SetColor(RGBAColor{ 0, 0, 0, 0xFF });
		SDL::Instance().ClearScene();
		grid.Render(drawField);
		SDL::Instance().ClearRenderTarget();
		
		//change = false;
	}

	s.Render(drawField.x, drawField.y);
	
}
