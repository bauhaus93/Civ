#include "TilesetSimple.h"

using namespace std;

TilesetSimple::TilesetSimple(unsigned int resourceChance_):
	Tileset{ resourceChance_ }{
}

TilesetSimple::~TilesetSimple(){
}

void TilesetSimple::CompleteTile(Tile& tile) {
	SDL_Rect rect{ 0, 0, 64, 32 };
	unique_ptr<Sprite> sprite = make_unique<Sprite>(*floor.at(common::Random(floor.size())), rect);

	if (common::Random() < resourceChance){
		cout << "RESOURCE!" << endl;
		tile.SetResource(true);
		sprite->Add(*resource.at(common::Random(resource.size())), rect);
	}
	tile.SetSprite(move(sprite));
}


