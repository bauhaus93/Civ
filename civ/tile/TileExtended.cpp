#include "TileExtended.h"

using namespace std;

TileExtended::TileExtended(const Tileset& tileset_):
	Tile{ tileset_ }{
}


TileExtended::~TileExtended(){
}

void TileExtended::CreateTileSprite(uint8_t neighbourMask){
	sprite = make_unique<Sprite>(floor);

	
	
	if (resource > -1){
		AddSprite(tileset.GetResource(resource).GetSprite());
	}

}
