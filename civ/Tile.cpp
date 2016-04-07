#include "Tile.h"

using namespace std;


Tile::Tile():
	hasResource{ false }{
}


Tile::~Tile(){
}

void Tile::SetSprite(unique_ptr<Sprite> sprite_){
	sprite = move(sprite_);
}

void Tile::Render(int x, int y){

	sprite->Render(x, y);
}


