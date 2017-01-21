#include "Map.h"

using namespace std;

Map::Map(const Rect& drawField_) :
	drawField{ drawField_ },
	tileFactory{},
	grid{}{

	SpriteFactory spriteFactory;
	WorldGenerator wg;




	spriteFactory.AddSpriteSheet("bmp/TERRAIN1.bmp", "terrain1");
	grid.SetMouseClickComparator(spriteFactory.CreateDiamondSprite("terrain1", Point{ 66, 447 }));	//TODO move in Grid
	grid.Create(75, 120);
	grid.AlignViewToCenter(drawField.w, drawField.h);

	LoadTilesets();
	wg.Generate(grid, tileFactory);

	change = true;

}


Map::~Map(){

}

void Map::Clicked(int screenX, int screenY){
	screenX -= drawField.x;
	screenY -= drawField.y;

	if (screenX >= 0 && screenX < drawField.w && screenY >= 0 && screenY < drawField.h){
		grid.CenterToClick(screenX, screenY, drawField.w, drawField.h);
	}
	change = true;
}

void Map::LoadTilesets(){
	Point pos{ 1, 1 };

	Logger::Write("Loading Tilesets");

	tileFactory.AddSimpleTileset("desert", RESOURCE_CHANCE);
	for(int i = 0; i < 4; i++){
		if(i < 2)
			tileFactory.AddFloor("desert", pos);
		else
			tileFactory.AddResource("desert", pos);
		pos.x += 65;
	}

	pos.x = 1;
	pos.y += 33;
	tileFactory.AddSimpleTileset("prairie", RESOURCE_CHANCE);
	for(int i = 0; i < 3; i++){
		if(i == 0){
			tileFactory.AddFloor("prairie", pos);
			pos.x += 65;
		}
		else
			tileFactory.AddResource("prairie", pos);
		pos.x += 65;
	}

	pos.x = 1;
	pos.y += 33;
	tileFactory.AddSimpleTileset("grasslands", RESOURCE_CHANCE);
	tileFactory.AddFloor("grasslands", pos);
	tileFactory.AddResource("grasslands", Point{ 456, 232 });

	pos.x = 1;
	pos.y += 33 * 4;

	const string names[] = {"tundra", "arctic", "swamp"};
	for(int i = 0; i < 3; i++){
		tileFactory.AddSimpleTileset(names[i], RESOURCE_CHANCE);
		for(int j = 0; j < 3; j++){
			if(j == 0){
				tileFactory.AddFloor(names[i], pos);
				pos.x += 65;
			}
			else
				tileFactory.AddResource(names[i], pos);
			pos.x += 65;
		}
		pos.x = 1;
		pos.y += 33;
	}
	tileFactory.AddSimpleTileset("jungle", RESOURCE_CHANCE);
	for(int i = 0; i < 4; i++){
		if(i < 2)
			tileFactory.AddFloor("jungle", pos);
		else
			tileFactory.AddResource("jungle", pos);
		pos.x += 65;
	}
	Logger::Write("Tilesets loaded");
}

void Map::Render(){
	grid.Render(drawField);
}
