#include "Map.h"

using namespace std;

Map::Map(const Rect& drawField_) :
	drawField{ drawField_ },
	tileFactory{},
	grid{}{

	SpriteFactory spriteFactory;

	spriteFactory.AddSpriteSheet("bmp/TERRAIN1.bmp", "terrain1");
	grid.SetMouseClickComparator(spriteFactory.CreateDiamondSprite("terrain1", Point{ 66, 447 }));	//TODO move in Grid


	LoadTilesets();



	grid.Create(75, 120);
	grid.AlignViewToCenter(drawField.w, drawField.h);

	WorldGenerator wg{tileFactory, random_device{}()};
	wg.Generate(grid);

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
	Logger::Write("Loading Tilesets");

	LoadBasicTilesets();
	LoadExtendedTilesets();
	LoadOceanTileset();

	Logger::Write("Tilesets loaded");
}

void Map::LoadBasicTilesets(){
	Point pos{ 1, 1 };

	tileFactory.AddBasicTileset("desert", RESOURCE_CHANCE);
	for(int i = 0; i < 4; i++){
		if(i < 2)
			tileFactory.AddBasicSprite("desert", pos);
		else
			tileFactory.AddResource("desert", pos);
		pos.x += 65;
	}

	pos.x = 1;
	pos.y += 33;
	tileFactory.AddBasicTileset("prairie", RESOURCE_CHANCE);
	for(int i = 0; i < 3; i++){
		if(i == 0){
			tileFactory.AddBasicSprite("prairie", pos);
			pos.x += 65;
		}
		else
			tileFactory.AddResource("prairie", pos);
		pos.x += 65;
	}

	pos.x = 1;
	pos.y += 33;
	tileFactory.AddBasicTileset("grasslands", RESOURCE_CHANCE);
	tileFactory.AddBasicSprite("grasslands", pos);
	tileFactory.AddResource("grasslands", Point{ 456, 232 });

	pos.x = 1;
	pos.y += 33 * 4;

	const string names[] = {"tundra", "arctic", "swamp"};
	for(int i = 0; i < 3; i++){
		tileFactory.AddBasicTileset(names[i], RESOURCE_CHANCE);
		for(int j = 0; j < 3; j++){
			if(j == 0){
				tileFactory.AddBasicSprite(names[i], pos);
				pos.x += 65;
			}
			else
				tileFactory.AddResource(names[i], pos);
			pos.x += 65;
		}
		pos.x = 1;
		pos.y += 33;
	}
	tileFactory.AddBasicTileset("jungle", RESOURCE_CHANCE);
	for(int i = 0; i < 4; i++){
		if(i < 2)
			tileFactory.AddBasicSprite("jungle", pos);
		else
			tileFactory.AddResource("jungle", pos);
		pos.x += 65;
	}
}

void Map::LoadExtendedTilesets(){
	Point pos{ 1, 133 };
	Point resourcePos{ 131, 100};
	Point fillerPos{ 1, 100 };
	const string namesT1[] = {"forest", "hills", "mountains"};
	const string namesT2[] = {"forest", "mountains", "hills"};

	for(int i = 0; i < 3; i++){
		tileFactory.AddExtendedTileset(namesT1[i], RESOURCE_CHANCE);
		tileFactory.AddBasicSprite(namesT1[i], fillerPos);
		for(int j = 0; j < 2; j++)
			tileFactory.AddResource(namesT1[i], Point{ resourcePos.x + j * 65, resourcePos.y + i * 33});
	}

	for(uint8_t mask = 0; mask < 16; mask++){
		for(int i = 0; i < 3; i++)
			tileFactory.AddExtendedSprite(namesT2[i], Point{ pos.x, pos.y + i * 66}, mask);
		if(mask == 7){
			pos.x = 1;
			pos.y += 33;
		}
		else
			pos.x += 65;
	}
}

void Map::LoadOceanTileset(){
	Point pos{ 1, 331 };

	tileFactory.AddOceanTileset("ocean", RESOURCE_CHANCE);
	tileFactory.AddBasicSprite("ocean", pos);
	pos.x += 65 * 2;

	for(int i = 0; i < 2; i++){
		tileFactory.AddResource("ocean", pos);
		pos.x += 65;
	}

	pos.x = 67;
	pos.y = 429;	//STD POS = 429, DEBUG = 378

	for(int i = 0; i < 4; i++){
		for(uint8_t j = 1; j < 8; j++){
			tileFactory.AddCoastline("ocean", pos, j << (8 * i));
			pos.x += 66;
		}
		if(i < 2){
			pos.x = 67;
			pos.y += 17;
		}
		else
			pos.x = 100;
	}




}

void Map::Render(){
	grid.Render(drawField);
}
