#include "Tile.h"

using namespace std;


Tile::Tile(const Tileset& tileset_ ) :
	tileset{ tileset_ },
	floor{tileset.GetRandomFloor()},
	resource{ tileset.GetRandomResource() }{


}

Tile::~Tile(){

}

void Tile::InitializeSprite(uint8_t neighbourMask){
	sprite = make_unique<Sprite>(floor);
	if (resource > -1){
		AddSprite(tileset.GetResource(resource).GetSprite());
	}
}

void Tile::AddSprite(const Sprite& add){
	sprite->Add(add);
}

void Tile::Render(int x, int y){
	sprite->Render(x, y);
}



