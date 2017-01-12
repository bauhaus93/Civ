#include "TileSimple.h"

using namespace std;

TileSimple::TileSimple(const Tileset& tileset_):
	Tile{ tileset_ }{
}


TileSimple::~TileSimple(){
}

void TileSimple::CreateTileSprite(uint8_t neighbourMask){
	sprite = make_unique<Sprite>(floor);
	if (resource > -1){
		AddSprite(tileset.GetResource(resource).GetSprite());
	}
}