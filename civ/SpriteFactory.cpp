#include "SpriteFactory.h"

using namespace std;

SpriteFactory::SpriteFactory(void){
}


SpriteFactory::~SpriteFactory(void){
	for (auto iter : baseImgs)
		SDL_FreeSurface(iter.second);
	baseImgs.clear();
}

void SpriteFactory::AddImage(const string& path, const string& name){
	SDL_Surface *tmp = SDL_LoadBMP(path.c_str());
	SDL_Surface *img = nullptr;
	SDL_Rect rect{ 0, 0, 0, 0 };
	

	if (tmp == nullptr)
		throw SDLException("SDL_LoadBMP");
	rect.w = tmp->w;
	rect.h = tmp->h;

	img = SDL_CreateRGBSurface(0, rect.w, rect.h, (Uint32)32, (Uint32)0xFF, (Uint32)0xFF << 8, (Uint32)0xFF << 16, (Uint32)0xFF << 24);

	if (img == nullptr){
		SDL_FreeSurface(tmp);
		throw SDLException("SDL_CreateRGBSurface");
	}

	if (SDL_BlitSurface(tmp, &rect, img, &rect) == -1){
		SDL_FreeSurface(img);
		SDL_FreeSurface(tmp);
		throw SDLException("SDL_BlitSurface");
	}
		
	baseImgs.insert(make_pair(name, img));
}

void SpriteFactory::AddTransparent(uint8_t rT, uint8_t gT, uint8_t bT){

	for (auto iter : baseImgs){
		SDL_Surface* surf = iter.second;

		SDL_LockSurface(surf);

		uint32_t *ptr = (uint32_t*)surf->pixels;

		for (int i = 0; i < surf->h*surf->w; i++){
			uint8_t r = static_cast<uint8_t>((*ptr & surf->format->Rmask) >> surf->format->Rshift);
			uint8_t g = static_cast<uint8_t>((*ptr & surf->format->Gmask) >> surf->format->Gshift);
			uint8_t b = static_cast<uint8_t>((*ptr & surf->format->Bmask) >> surf->format->Bshift);

			if (r == rT && g == gT && b == bT){
				*ptr = ((r << surf->format->Rshift) + (g << surf->format->Gshift) + (b << surf->format->Bshift));
			}
			ptr++;
		}
		SDL_UnlockSurface(surf);
	}
	
}

Sprite SpriteFactory::CreateSprite(const string& name, const Rect& dim){

	return Sprite(baseImgs.at(name), dim);
}

Sprite SpriteFactory::CreateDiamondSprite(const string& name, int x, int y){
	const Rect rect = { x, y, 64, 32 };
	return CreateSprite(name, rect);
}
