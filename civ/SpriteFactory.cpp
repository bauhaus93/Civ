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
	SDL_Surface *img = SDL_LoadBMP(path.c_str());

	if (img == nullptr)
		throw SDLException("SDL_LoadBMP");

	baseImgs.insert(make_pair(name, img));
}

std::unique_ptr<Sprite> SpriteFactory::CreateSprite(const string& name, const SDL_Rect& dim, uint32_t colorKey){
	unique_ptr<Sprite> sprite = nullptr;
	SDL_Surface *s = nullptr;

	try{
		 s = baseImgs.at(name);
	}
	catch (const out_of_range& e){
		common::Log(e);
		return nullptr;
	}

	try{
		if (SDL_SetColorKey(s, true, colorKey) == -1)
			throw SDLException("SDL_SetColorKey");

		sprite = make_unique<Sprite>(baseImgs.at(name), dim);
	}
	catch (const SDLException& e){
		common::Log(e);
		return nullptr;
	}

	return move(sprite);
}

std::unique_ptr<Sprite> SpriteFactory::CreateDiamondSprite(const string& name, int x, int y, uint32_t colorKey){
	const SDL_Rect rect = { x, y, 64, 32 };
	return move(CreateSprite(name, rect, colorKey));
}
