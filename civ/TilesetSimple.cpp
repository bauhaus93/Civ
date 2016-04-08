#include "TilesetSimple.h"

using namespace std;

TilesetSimple::TilesetSimple(unsigned int resourceChance_):
	Tileset{ resourceChance_ }{
}

TilesetSimple::~TilesetSimple(){
}

void TilesetSimple::InitiateTile(Tile& tile){
	tile.AddSubTile(SubTileType::FLOOR, common::Random(floor.size()));
	if(common::Random() < resourceChance)
		tile.AddSubTile(SubTileType::RESOURCE, common::Random(resource.size()));
}

void TilesetSimple::CreateTileSprite(Tile& tile) {
	SDL_Rect rect{ 0, 0, 64, 32 };
	unique_ptr<Sprite> sprite = nullptr;

	
	auto subTiles = tile.GetSubTiles();
	auto it = find_if(subTiles.begin(), subTiles.end(), [](SubTile st){ return st.type==SubTileType::FLOOR; });

	if(it != subTiles.end()){
		sprite = make_unique<Sprite>(*floor.at((*it).index), rect);
	}



	tile.SetSprite(move(sprite));
}


