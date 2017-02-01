#include "SDLSprite.h"

using namespace std;

static void TextureOnTexture(SDL_Texture *src, const SDL_Rect& srcRect, SDL_Texture *dest, const SDL_Rect& destRect);

inline Rect ToRect(const SDL_Rect& rect){
	return Rect{rect.x, rect.y, rect.w, rect.h};
}

inline SDL_Rect ToSDLRect(const Rect& rect){
	return SDL_Rect{ rect.x, rect.y, rect.w, rect.h };
}

SDLSprite::SDLSprite() :
	texture{ nullptr },
	rect{ 0, 0, 0, 0 },
	hash{ 0 }{
}

SDLSprite::SDLSprite(SDL_Surface* src, const Rect& dim_) :
	SDLSprite{}{
	SDL_Rect dim = ToSDLRect(dim_);

	SDL_Surface *surf = SDL_CreateRGBSurface(0, dim.w, dim.h, (Uint32)32, (Uint32)0xFF, (Uint32)0xFF << 8, (Uint32)0xFF << 16, (Uint32)0xFF << 24);

	if (surf == nullptr)
		throw SDLException("SDL_CreateRGBSurface");

	if (SDL_BlitSurface(src, &dim, surf, nullptr) == -1)
		throw SDLException("SDL_BlitSurface");

	//make texture SDL_TEXTUREACCESS_TARGET
	SDL_Texture *tmp = SDL_CreateTextureFromSurface(SDLEngine::Instance().GetRenderer(), surf);
	SDL_FreeSurface(surf);

	texture = SDL_CreateTexture(SDLEngine::Instance().GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, dim.w, dim.h);
	SDL_Rect tmpRect{ 0, 0, dim.w, dim.h };
	TextureOnTexture(tmp, tmpRect, texture, tmpRect);
	SDL_DestroyTexture(tmp);

	if (texture == nullptr)
		throw SDLException("SDL_CreateTextureFromSurface");

	if (SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND) == -1)
		throw SDLException("SDL_SetTextureBlendMode");

	if (SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h) == -1)
		throw SDLException("SDL_QueryTexture");
	CalculateHash();
}

SDLSprite::SDLSprite(const SDLSprite& other, const Rect& dim_):
	SDLSprite(Dimension{ dim_.w, dim_.h }){
	SDL_Rect dim = ToSDLRect(dim_);
	TextureOnTexture(other.texture, dim, texture, SDL_Rect{0, 0, rect.w, rect.h});
	CalculateHash();
}

SDLSprite::SDLSprite(const Dimension& size) :
	texture{ nullptr },
	rect{ 0, 0, size.x, size.y },
	hash{ 0 }{

	texture = SDL_CreateTexture(SDLEngine::Instance().GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rect.w, rect.h);

	if (texture == nullptr)
		throw SDLException("SDL_CreateTexture");
}

SDLSprite::SDLSprite(SDLSprite&& other) noexcept:
	texture{ other.texture },
	rect{ other.rect.x, other.rect.y, other.rect.w, other.rect.h },
	hash{ other.hash }{
	other.texture = nullptr;
}

SDLSprite& SDLSprite::operator=(SDLSprite&& other) noexcept{
	texture = other.texture;
	rect.x = other.rect.x;
	rect.y = other.rect.y;
	rect.w = other.rect.w;
	rect.h = other.rect.h;
	hash = other.hash;
	other.texture = nullptr;	//FUCK YOU
	return *this;
}

SDLSprite::~SDLSprite(){
	if (texture != nullptr)
		SDL_DestroyTexture(texture);	//FUCK YOU TOO
}

void SDLSprite::Add(const SDLSprite& sprite, const Point& src, const Point& dest){
	TextureOnTexture(sprite.texture, SDL_Rect{src.x, src.y, sprite.GetWidth(), sprite.GetHeight()}, texture, SDL_Rect{dest.x, dest.y, sprite.GetWidth(), sprite.GetHeight()});
	CalculateHash();
}

void SDLSprite::Add(const SDLSprite& SDLSprite){
	const Point zero{0, 0};
	Add(SDLSprite, zero, zero);
}

void SDLSprite::SetAsRenderTarget(){
	if (SDL_SetRenderTarget(SDLEngine::Instance().GetRenderer(), texture) == -1)
		throw SDLException("SDL_SetRenderTarget");
}

void SDLSprite::Render(int x, int y) const{
	SDL_Rect r{ x, y, rect.w, rect.h};

	if (SDL_RenderCopy(SDLEngine::Instance().GetRenderer(), texture, nullptr, &r) == -1)
		throw SDLException("SDL_RenderCopy");
}

Uint32 SDLSprite::GetFormat() const{
	Uint32 format;
	if (SDL_QueryTexture(texture, &format, nullptr, nullptr, nullptr) == -1)
		throw SDLException("SDL_QueryTexture");
	return format;
}

const SDL_Rect& SDLSprite::GetRect() const{
	return rect;
}

int SDLSprite::GetWidth() const{
	return rect.w;
}

int SDLSprite::GetHeight() const{
	return rect.h;
}

RGBAColor SDLSprite::PixelAt(int x, int y){
	uint32_t pixels = 0;
	SDL_Rect r{ x, y, 1, 1 };

	if (SDL_SetRenderTarget(SDLEngine::Instance().GetRenderer(), texture) == -1)
		throw SDLException("SDL_SetRenderTarget");

	if (SDL_RenderReadPixels(SDLEngine::Instance().GetRenderer(), &r, SDL_PIXELFORMAT_RGBA8888, &pixels, 4*rect.w) < 0)	//FUCK YOU
		throw SDLException("SDL_RenderReadPixels");

	if (SDL_SetRenderTarget(SDLEngine::Instance().GetRenderer(), nullptr) == -1)
		throw SDLException("SDL_SetRenderTarget");

	return RGBAColor{	static_cast<uint8_t>((pixels >> 24)),
						static_cast<uint8_t>((pixels >> 16)),
						static_cast<uint8_t>((pixels >> 8)),
						static_cast<uint8_t>(pixels) };	//removed all & 0xFF bc pixels are cast to uint8_t
}

void SDLSprite::CalculateHash(){

	if (SDL_SetRenderTarget(SDLEngine::Instance().GetRenderer(), texture) == -1)
		throw SDLException("SDL_SetRenderTarget");


	SDL_Surface* surf = SDL_CreateRGBSurface(0, rect.w, rect.h, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);

	if(surf == nullptr)
		throw SDLException("SDL_CreateRGBSurface");

	if (SDL_RenderReadPixels(SDLEngine::Instance().GetRenderer(), nullptr, SDL_PIXELFORMAT_RGBA8888, surf->pixels, 4*rect.w) < 0){
		SDL_FreeSurface(surf);
		throw SDLException("SDL_RenderReadPixels");
	}

	uint32_t* ptr = (uint32_t*)surf->pixels;
	hash = 0;
	for(int x = 0; x < rect.w; x++){
		for(int y = 0; y < rect.h; y++){
			hash += *ptr;
			hash += hash << 10;
			hash ^= hash >> 6;
			ptr++;
		}
	}

	hash += hash << 3;
	hash ^= hash >> 11;
	hash += hash << 15;

	SDL_FreeSurface(surf);

	if (SDL_SetRenderTarget(SDLEngine::Instance().GetRenderer(), nullptr) == -1)
		throw SDLException("SDL_SetRenderTarget");

	assert(hash != 0);	//zero is reserved
}

uint32_t SDLSprite::GetHash() const{
	return hash;
}

static void TextureOnTexture(SDL_Texture *src, const SDL_Rect& srcRect, SDL_Texture *dest, const SDL_Rect& destRect){
	if (SDL_SetTextureBlendMode(dest, SDL_BLENDMODE_BLEND) == -1)
		throw SDLException("SDL_SetTextureBlendMode");

	if (SDL_SetRenderTarget(SDLEngine::Instance().GetRenderer(), dest) == -1)
		throw SDLException("SDL_SetRenderTarget");

	if (SDL_RenderCopy(SDLEngine::Instance().GetRenderer(), src, &srcRect, &destRect) == -1)
		throw SDLException("SDL_RenderCopy");

	if (SDL_SetRenderTarget(SDLEngine::Instance().GetRenderer(), nullptr) == -1)
		throw SDLException("SDL_SetRenderTarget");
}
