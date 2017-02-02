#include "Map.h"

using namespace std;

Map::Map(const Rect& drawField_) :
	drawField{ drawField_ },
	tilesetManager{ 7 },
	grid{}{


	grid.Create(75, 120);
	grid.AlignViewToCenter(drawField.w, drawField.h);

	WorldGenerator wg{tilesetManager, random_device{}()};
	wg.Generate(grid);

	change = true;

}

void Map::Clicked(int screenX, int screenY){
	screenX -= drawField.x;
	screenY -= drawField.y;

	if (screenX >= 0 && screenX < drawField.w && screenY >= 0 && screenY < drawField.h){
		grid.CenterToClick(screenX, screenY, drawField.w, drawField.h);
	}
	change = true;
}

void Map::Render(){
	grid.Render(drawField);
}
