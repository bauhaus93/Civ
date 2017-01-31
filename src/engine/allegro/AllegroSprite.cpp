#include "AllegroSprite.h"

AllegroSprite::AllegroSprite() :
	bmp{ nullptr },
	size{ 0, 0 },
	hash{ 0 }{
}

//Important: Rect gives starting point + width/height of rectangle!
AllegroSprite::AllegroSprite(const AllegroSprite& sprite, const Rect& srcRect) :
	AllegroSprite(Dimension{ srcRect.w, srcRect.h }){
	al_set_target_bitmap(bmp);
	al_draw_bitmap_region(sprite.bmp, srcRect.x, srcRect.y, srcRect.x + srcRect.w, srcRect.y + srcRect.h, 0, 0, 0);
	al_set_target_bitmap(al_get_backbuffer(AllegroEngine::Instance().GetDisplay()));
	CalculateHash();
}

AllegroSprite::AllegroSprite(const Dimension& size_):
	bmp { al_create_bitmap(size_.x, size_.y) },
	size{ size_ },
	hash{ 0 }{

	if (bmp == nullptr)
		throw AllegroException("al_create_bitmap");

}

AllegroSprite::AllegroSprite(const std::string& filename):
	AllegroSprite()	{
	bmp = al_load_bitmap(filename.c_str());

	if (bmp == nullptr)
		throw AllegroException("al_load_bitmap");

	size.x = al_get_bitmap_width(bmp);
	size.y = al_get_bitmap_height(bmp);
	CalculateHash();
}

AllegroSprite::AllegroSprite(AllegroSprite&& other) noexcept:
	bmp{ other.bmp },
	size{ other.GetWidth(), other.GetHeight()},
	hash{ other.hash }{
	other.bmp = nullptr;
}

//TODO maybe check if caller has already a bmp? (also in SDLSprite)
AllegroSprite& AllegroSprite::operator=(AllegroSprite&& other) noexcept{
	bmp = other.bmp;
	hash = other.hash;
	size.x = other.GetWidth();
	size.y = other.GetHeight();
	other.bmp = nullptr;
	return *this;
}

AllegroSprite::~AllegroSprite(){
	if (bmp != nullptr){
		al_destroy_bitmap(bmp);
		bmp = nullptr;
	}
}

void AllegroSprite::MakeColorTransparent(const RGBColor& color){

	int bmpH = al_get_bitmap_height(bmp);
	int bmpW = al_get_bitmap_width(bmp);

	ALLEGRO_LOCKED_REGION* region = al_lock_bitmap(bmp, ALLEGRO_PIXEL_FORMAT_ARGB_8888, ALLEGRO_LOCK_READWRITE);
	if (region == nullptr)
		throw AllegroException("al_lock_bitmap");

	assert(region->pixel_size == 4);

	for(int x = 0; x < bmpW; x++){
		for(int y = 0; y < bmpH; y++){
			uint32_t* ptr = (uint32_t*)(((uint8_t*)region->data) + region->pitch*y + 4 * x);

			uint8_t r = (*ptr & 0x00FF0000) >> 16;
			uint8_t g = (*ptr & 0x0000FF00) >> 8;
			uint8_t b = (*ptr & 0x000000FF);

			if (r == color.r && g == color.g && b == color.b)
				*ptr = (*ptr & 0x00FFFFFF);

		}
	}

	al_unlock_bitmap(bmp);
	//TODO maybe free region?
}

int AllegroSprite::GetWidth() const{
	return al_get_bitmap_width(bmp);
}

int AllegroSprite::GetHeight() const{
	return al_get_bitmap_height(bmp);
}

void AllegroSprite::Add(const AllegroSprite& add){
	const Point zero{0, 0};
	Add(add, zero, zero);
}

void AllegroSprite::Add(const AllegroSprite& add, const Point& src, const Point& dest){
	al_set_target_bitmap(bmp);
	al_draw_bitmap_region(add.bmp, src.x, src.y, add.GetWidth(), add.GetHeight(), dest.x, dest.y, 0);
	al_set_target_bitmap(al_get_backbuffer(AllegroEngine::Instance().GetDisplay()));
	CalculateHash();
}

void AllegroSprite::Render(int x, int y) const{
	al_draw_bitmap(bmp, x, y, 0);
}

void AllegroSprite::SetAsRenderTarget(){
	al_set_target_bitmap(bmp);
}

RGBAColor AllegroSprite::PixelAt(int x, int y){
	RGBAColor col;
	al_unmap_rgba(al_get_pixel(bmp, x, y), &col.r, &col.g, &col.b, &col.a);
	return col;
}

/*Important: Don't mix up composite hashes with the sprite hashes
Sprite hashes are calculated by the pixels of the sprite
Composite hashes are calculated by the hashes of the sprites of which the composite consists
So the composite hash of a sprite and the hash of the sprite do not match!*/
void AllegroSprite::CalculateHash(){
	int bmpH = al_get_bitmap_height(bmp);
	int bmpW = al_get_bitmap_width(bmp);


	ALLEGRO_LOCKED_REGION* region = al_lock_bitmap(bmp, ALLEGRO_PIXEL_FORMAT_ARGB_8888, ALLEGRO_LOCK_READWRITE);
	if (region == nullptr)
		throw AllegroException("al_lock_bitmap");

	assert(region->pixel_size == 4);

	hash = 0;
	for(int x = 0; x < bmpW; x++){
		for(int y = 0; y < bmpH; y++){
			uint32_t color = (uint32_t)*(((uint8_t*)region->data) + region->pitch*y + 4 * x);
			hash += color;
			hash += hash << 10;
			hash ^= hash >> 6;

		}
	}
	al_unlock_bitmap(bmp);

	hash += hash << 3;
	hash ^= hash >> 11;
	hash += hash << 15;

	assert(hash != 0);	//zero is reserved
}

uint32_t AllegroSprite::GetHash() const{
	return hash;
}
