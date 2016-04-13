#include "TilesetSimple.h"

using namespace std;

TilesetSimple::TilesetSimple(const string& name_, unsigned int resourceChance_):
	Tileset{ name_, resourceChance_ }{
}

TilesetSimple::~TilesetSimple(void){

}

std::unique_ptr<Tile> TilesetSimple::CreateTile(void){
	unique_ptr<Tile> tile = make_unique<Tile>(*floor.at(common::Random(floor.size())));

	if (common::Random() < resourceChance)
		tile->SetResource(common::Random(resource.size()));

	return move(tile);
}

void TilesetSimple::CreateTileSprite(Tile& tile) {
	constexpr SDL_Rect rect{ 0, 0, 64, 32 };

	tile.InitializeSprite();

	int resID = tile.GetResource();
	if (resID != -1){
		tile.AddSprite(*resource.at(resID));
	}
	
}


