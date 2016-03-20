#include "Sprite.h"

using namespace std;

Sprite::Sprite(SDL_Surface* src, const SDL_Rect& dim):
	texture{ nullptr },
	rect{ 0, 0, 0, 0 }{

	SDL_Surface *surf = SDL_CreateRGBSurface(0, dim.w, dim.h, 32, 0xFF, 0xFF<<8, 0xFF<<16, 0xFF<<24);

	if (surf == nullptr)
		throw SDLException("SDL_CreateRGBSurface");

	if (SDL_BlitSurface(src, &dim, surf, nullptr) == -1)
		throw SDLException("SDL_BlitSurface");

	texture = SDL_CreateTextureFromSurface(SDL::GetRenderer(), surf);
	SDL_FreeSurface(surf);
	
	if (texture == nullptr)
		throw SDLException("SDL_CreateTextureFromSurface");

	if (SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND) == -1)
		throw SDLException("SDL_SetTextureBlendMode");

	if (SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h) == -1)
		throw SDLException("SDL_QueryTexture");
}

Sprite::Sprite(const Sprite& sprite, const SDL_Rect& dim):
	texture{ nullptr },
	rect{0, 0, dim.w, dim.h}{

	texture = SDL_CreateTexture(SDL::GetRenderer(), sprite.GetFormat(), SDL_TEXTUREACCESS_TARGET, rect.w, rect.h);

	if (texture == nullptr)
		throw SDLException("SDL_CreateTexture");

	if (SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND) == -1)
		throw SDLException("SDL_SetTextureBlendMode");

	if (SDL_SetRenderTarget(SDL::GetRenderer(), texture) == -1)
		throw SDLException("SDL_SetRenderTarget");

	if (SDL_RenderCopy(SDL::GetRenderer(), sprite.texture, &dim, &rect) == -1)
		throw SDLException("SDL_RenderCopy");

	if (SDL_SetRenderTarget(SDL::GetRenderer(), nullptr) == -1)
		throw SDLException("SDL_SetRenderTarget");
}


Sprite::~Sprite(void){
	if (texture != nullptr)
		SDL_DestroyTexture(texture);
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
