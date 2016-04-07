#include "TileSprite.h"


TileSprite::TileSprite():
	sprite{ SDL_Rect{0, 0, 64, 32} }{


}


TileSprite::~TileSprite(){
}

void TileSprite::Render(int x, int y){
	sprite.Render(x, y);
}

void TileSprite::AddSprite(const Sprite& addedSprite){
	SDL_Rect rect{ 0, 0, 64, 32 };
	sprite.Add(addedSprite, rect);
}
