#include "TileExtended.h"

using namespace std;

TileExtended::TileExtended(const Tileset& tileset_):
	Tile{ tileset_ }{
}


TileExtended::~TileExtended(){
}

void TileExtended::CreateTileSprite(uint8_t neighbourMask){
	sprite = make_unique<Sprite>(floor);

	AddSprite(tileset.GetExtension(neighbourMask & 0xF));	//applies to forest/hills/mountains, masks > 0xF needed for coastline	

	if (resource > -1)
		AddSprite(tileset.GetResource(resource).GetSprite());

}
