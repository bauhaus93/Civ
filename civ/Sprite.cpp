#include "Sprite.h"

using namespace std;

static void TextureOnTexture(SDL_Texture *src, const SDL_Rect& srcRect, SDL_Texture *dest, const SDL_Rect& destRect);

inline Rect ToRect(const SDL_Rect& rect){
	Rect r{ rect.x, rect.y, rect.w, rect.h };
	return std::move(r);
}

inline SDL_Rect ToSDLRect(const Rect& rect){
	SDL_Rect r{ rect.x, rect.y, rect.w, rect.h };
	return r;
}

Sprite::Sprite(void) :
	texture{ nullptr },
	rect{ 0, 0, 0, 0 }{
}

Sprite::Sprite(SDL_Surface* src, const Rect& dim_) :
	Sprite{}{
	SDL_Rect dim = ToSDLRect(dim_);

	SDL_Surface *surf = SDL_CreateRGBSurface(0, dim.w, dim.h, (Uint32)32, (Uint32)0xFF, (Uint32)0xFF << 8, (Uint32)0xFF << 16, (Uint32)0xFF << 24);

	if (surf == nullptr)
		throw SDLException("SDL_CreateRGBSurface");

	if (SDL_BlitSurface(src, &dim, surf, nullptr) == -1)
		throw SDLException("SDL_BlitSurface");

	//make texture SDL_TEXTUREACCESS_TARGET
	SDL_Texture *tmp = SDL_CreateTextureFromSurface(SDL::Instance().GetRenderer(), surf);
	SDL_FreeSurface(surf);

	texture = SDL_CreateTexture(SDL::Instance().GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, dim.w, dim.h);
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

Sprite::Sprite(const Rect& dim) :
	texture{ nullptr },
	rect{ 0, 0, dim.w, dim.h }{

	texture = SDL_CreateTexture(SDL::Instance().GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, dim.w, dim.h);

	if (texture == nullptr)
		throw SDLException("SDL_CreateTexture");
}

Sprite::Sprite(const Sprite& src, const Rect& dim) :
	Sprite{ dim }{
	Add(src, dim);
}

Sprite::Sprite(const Sprite& src) :
	Sprite{ src, ToRect(src.GetRect()) }{
}

Sprite::Sprite(Sprite&& other) noexcept:
	texture{ other.texture },
	rect{ other.rect.x, other.rect.y, other.rect.w, other.rect.h }{
	other.texture = nullptr;
}

Sprite& Sprite::operator=(Sprite&& other) noexcept{
	texture = other.texture;
	rect.x = other.rect.x;
	rect.y = other.rect.y;
	rect.w = other.rect.w;
	rect.h = other.rect.h;
	other.texture = nullptr;	//FUCK YOU
	return *this;
}


Sprite::~Sprite(void){
	if (texture != nullptr)
		SDL_DestroyTexture(texture);	//FUCK YOU TOO
}

void Sprite::Add(const Sprite& sprite, const Rect& dim){
	TextureOnTexture(sprite.texture, ToSDLRect(dim), texture, rect);
}

void Sprite::Add(const Sprite& sprite){
	Add(sprite, ToRect(sprite.GetRect()));
}

void Sprite::SetAsRenderTarget(){
	if (SDL_SetRenderTarget(SDL::Instance().GetRenderer(), texture) == -1)
		throw SDLException("SDL_SetRenderTarget");
}

void Sprite::Render(int x, int y){
	rect.x = x;
	rect.y = y;
	if (SDL_RenderCopy(SDL::Instance().GetRenderer(), texture, nullptr, &rect) == -1)
		throw SDLException("SDL_RenderCopy");
}

Uint32 Sprite::GetFormat(void) const{
	Uint32 format;
	if (SDL_QueryTexture(texture, &format, nullptr, nullptr, nullptr) == -1)
		throw SDLException("SDL_QueryTexture");
	return format;
}

const SDL_Rect& Sprite::GetRect() const{
	return rect;
}

RGBAColor Sprite::PixelAt(int x, int y){
	uint32_t pixels = 0;
	SDL_Rect r{ x, y, 1, 1 };

	if (SDL_SetRenderTarget(SDL::Instance().GetRenderer(), texture) == -1)
		throw SDLException("SDL_SetRenderTarget");

	if (SDL_RenderReadPixels(SDL::Instance().GetRenderer(), &r, SDL_PIXELFORMAT_RGBA8888, &pixels, 4*rect.w) < 0)	//FUCK YOU
		throw SDLException("SDL_RenderReadPixels");

	if (SDL_SetRenderTarget(SDL::Instance().GetRenderer(), nullptr) == -1)
		throw SDLException("SDL_SetRenderTarget");

	return move(RGBAColor{ static_cast<uint8_t>((pixels >> 24) & 0xFF), static_cast<uint8_t>((pixels >> 16) & 0xFF), static_cast<uint8_t>((pixels >> 8) && 0xFF), static_cast<uint8_t>(pixels & 0xFF) });
}

static void TextureOnTexture(SDL_Texture *src, const SDL_Rect& srcRect, SDL_Texture *dest, const SDL_Rect& destRect){
	if (SDL_SetTextureBlendMode(dest, SDL_BLENDMODE_BLEND) == -1)
		throw SDLException("SDL_SetTextureBlendMode");

	if (SDL_SetRenderTarget(SDL::Instance().GetRenderer(), dest) == -1)
		throw SDLException("SDL_SetRenderTarget");

	if (SDL_RenderCopy(SDL::Instance().GetRenderer(), src, &srcRect, &destRect) == -1)
		throw SDLException("SDL_RenderCopy");

	if (SDL_SetRenderTarget(SDL::Instance().GetRenderer(), nullptr) == -1)
		throw SDLException("SDL_SetRenderTarget");
}
