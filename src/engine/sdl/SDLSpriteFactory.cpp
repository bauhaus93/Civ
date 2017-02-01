#include "SDLSpriteFactory.h"

using namespace std;

SDLSpriteFactory::SDLSpriteFactory(){
}


SDLSpriteFactory::~SDLSpriteFactory(){
	for (auto iter : baseImgs)
		SDL_FreeSurface(iter.second);
	baseImgs.clear();
}

void SDLSpriteFactory::AddSpriteSheet(const std::string& sheetname, const std::string& filename){
	SDL_Surface *tmp = nullptr;
	SDL_Surface *img = nullptr;
	SDL_Rect rect{ 0, 0, 0, 0 };

	if(baseImgs.find(sheetname) != baseImgs.end())
		throw CivException("SDLSpriteFactory::AddSpriteSheet", "Sheet \"" + sheetname + "\" already existing!");

 	tmp = SDL_LoadBMP(filename.c_str());
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
	SDL_FreeSurface(tmp);
	baseImgs.emplace(sheetname, img);
}

void SDLSpriteFactory::MakeTransparent(const RGBColor& color){

	for (auto iter : baseImgs){
		SDL_Surface* surf = iter.second;

		SDL_LockSurface(surf);

		uint32_t *ptr = (uint32_t*)surf->pixels;

		for (int i = 0; i < surf->h*surf->w; i++){
			uint8_t r = static_cast<uint8_t>((*ptr & surf->format->Rmask) >> surf->format->Rshift);
			uint8_t g = static_cast<uint8_t>((*ptr & surf->format->Gmask) >> surf->format->Gshift);
			uint8_t b = static_cast<uint8_t>((*ptr & surf->format->Bmask) >> surf->format->Bshift);

			if (r == color.r && g == color.g && b == color.b){
				*ptr = ((r << surf->format->Rshift) + (g << surf->format->Gshift) + (b << surf->format->Bshift));
			}
			ptr++;
		}
		SDL_UnlockSurface(surf);
	}

}

shared_ptr<SDLSprite> SDLSpriteFactory::CreateSprite(const string& name, const Rect& dim){
	try{
		return make_shared<SDLSprite>(baseImgs.at(name), dim);
	}
	catch (const out_of_range& e){
		throw CivException("SDLSpriteFactory::CreateSprite", "Map element " + name + " not existing");
	}
}

shared_ptr<SDLSprite> SDLSpriteFactory::CreateDiamondSprite(const string& name, const Point& pos){
	return CreateSprite(name, Rect{ pos.x, pos.y, 64, 32});
}
