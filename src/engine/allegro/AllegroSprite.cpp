#include "AllegroSprite.h"

AllegroSprite::AllegroSprite() :
	bmp{ nullptr }{
}

AllegroSprite::AllegroSprite(const AllegroSprite& sprite, const Rect& rect) :
	AllegroSprite(rect){
	al_set_target_bitmap(bmp);
	al_draw_bitmap_region(sprite.bmp, rect.x, rect.y, rect.w, rect.h, 0, 0, 0);
	al_set_target_bitmap(al_get_backbuffer(AllegroEngine::Instance().GetDisplay()));

}

AllegroSprite::AllegroSprite(const Rect& rect){
	bmp = al_create_bitmap(rect.w, rect.h);

	if (bmp == nullptr)
		throw AllegroException("al_create_bitmap");

}

AllegroSprite::AllegroSprite(const std::string& filename){
	bmp = al_load_bitmap(filename.c_str());

	if (bmp == nullptr)
		throw AllegroException("al_load_bitmap");
}

AllegroSprite::AllegroSprite(AllegroSprite&& other) noexcept:
	bmp{ other.bmp }{
	other.bmp = nullptr;

}

AllegroSprite::AllegroSprite(const AllegroSprite & other) :
	AllegroSprite{ other, Rect{0, 0,  other.GetWidth(), other.GetHeight()} }{

}

//TODO maybe check if caller has already a bmp? (also in SDLSprite)
AllegroSprite& AllegroSprite::operator=(AllegroSprite&& other) noexcept{
	bmp = other.bmp;
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
	Add(add, Rect{ 0, 0, add.GetWidth(), add.GetHeight() });
}

void AllegroSprite::Add(const AllegroSprite& add, const Rect& rect){
	al_set_target_bitmap(bmp);
	al_draw_bitmap_region(add.bmp, 0, 0, rect.w, rect.h, rect.x, rect.y, 0);
	al_set_target_bitmap(al_get_backbuffer(AllegroEngine::Instance().GetDisplay()));
}

void AllegroSprite::Render(int x, int y){
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
