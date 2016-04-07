#include "Sprite.h"

using namespace std;

Sprite::Sprite(SDL_Surface* src, const SDL_Rect& dim) :
	texture{ nullptr },
	rect{ 0, 0, 0, 0 }{

	SDL_Surface *surf = SDL_CreateRGBSurface(0, dim.w, dim.h, (Uint32)32, (Uint32)0xFF, (Uint32)0xFF << 8, (Uint32)0xFF << 16, (Uint32)0xFF << 24);

	if (surf == nullptr)
		throw SDLException("SDL_CreateRGBSurface");

	if (SDL_BlitSurface(src, &dim, surf, nullptr) == -1)
		throw SDLException("SDL_BlitSurface");

	//make texture SDL_TEXTUREACCESS_TARGET
	SDL_Texture *tmp = SDL_CreateTextureFromSurface(SDL::GetRenderer(), surf);
	SDL_FreeSurface(surf);

	texture = SDL_CreateTexture(SDL::GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, dim.w, dim.h);
	SDL_Rect tmpRect{ 0, 0, dim.w, dim.h };
	TextureOnTexture(tmp, tmpRect, texture, tmpRect);
	SDL_DestroyTexture(tmp);

	if (texture == nullptr)
		throw SDLException("SDL_CreateTextureFromSurface");

	if (SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND) == -1)
		throw SDLException("SDL_SetTextureBlendMode");

	if (SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h) == -1)
		throw SDLException("SDL_QueryTexture");
}

Sprite::Sprite(const SDL_Rect& dim) :
	texture{ nullptr },
	rect{ 0, 0, dim.w, dim.h }{

	texture = SDL_CreateTexture(SDL::GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, dim.w, dim.h);

	if (texture == nullptr)
		throw SDLException("SDL_CreateTexture");
}

Sprite::Sprite(const Sprite& src, const SDL_Rect& dim) :
	Sprite{ dim }{
	Add(src, dim);
}


Sprite::~Sprite(void){
	if (texture != nullptr)
		SDL_DestroyTexture(texture);
}

void Sprite::Add(const Sprite& sprite, const SDL_Rect& dim){
	TextureOnTexture(sprite.texture, dim, texture, rect);
}

void Sprite::Render(int x, int y){
	rect.x = x;
	rect.y = y;
	if (SDL_RenderCopy(SDL::GetRenderer(), texture, nullptr, &rect) == -1)
		throw SDLException("SDL_RenderCopy");
}

Uint32 Sprite::GetFormat(void) const{
	Uint32 format;
	if (SDL_QueryTexture(texture, &format, nullptr, nullptr, nullptr) == -1)
		throw SDLException("SDL_QueryTexture");
	return format;
}


void TextureOnTexture(SDL_Texture *src, const SDL_Rect& srcRect, SDL_Texture *dest, const SDL_Rect& destRect){
	if (SDL_SetTextureBlendMode(dest, SDL_BLENDMODE_BLEND) == -1)
		throw SDLException("SDL_SetTextureBlendMode");

	if (SDL_SetRenderTarget(SDL::GetRenderer(), dest) == -1)
		throw SDLException("SDL_SetRenderTarget");

	if (SDL_RenderCopy(SDL::GetRenderer(), src, &srcRect, &destRect) == -1)
		throw SDLException("SDL_RenderCopy");

	if (SDL_SetRenderTarget(SDL::GetRenderer(), nullptr) == -1)
		throw SDLException("SDL_SetRenderTarget");
}