#include "Tile.h"

using namespace std;


Tile::Tile(TileType type_, Sprite& floor_) :
	type{ type_ },
	floor{ floor_ },
	resource{ -1 }{
}


Tile::~Tile(){
}

void Tile::SetResource(int newResource){
	resource = newResource;
}

void Tile::InitializeSprite(void){
	sprite = make_unique<Sprite>(floor);
}

void Tile::AddSprite(Sprite& add){
	sprite->Add(add);
}

int Tile::GetResource(void) const{
	return resource;
}


void Tile::Render(int x, int y){
	sprite->Render(x, y);
}


