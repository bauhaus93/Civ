#include "AllegroSpriteFactory.h"



AllegroSpriteFactory::AllegroSpriteFactory(){
	al_set_new_bitmap_format(ALLEGRO_PIXEL_FORMAT_ARGB_8888);
}


AllegroSpriteFactory::~AllegroSpriteFactory(){
	sprites.clear();
}

void AllegroSpriteFactory::AddSpriteSheet(const std::string& filename, const std::string& sheetname){
	sprites.emplace(make_pair(sheetname, filename));
}

void AllegroSpriteFactory::MakeTransparent(const RGBColor& color){
	for (auto& iter : sprites){
		iter.second.MakeColorTransparent(color);
	}
}

AllegroSprite AllegroSpriteFactory::CreateSprite(const std::string& sheetname, const Rect& dim){
	try{
		return AllegroSprite(sprites.at(sheetname), dim);
	}
	catch (const std::out_of_range& e){
		throw CivException("AllegroSpriteFactory::CreateSprite", "Map element " + sheetname + " not existing");
	}
}

AllegroSprite AllegroSpriteFactory::CreateDiamondSprite(const std::string& sheetname, const Point& pos){
	try{
		return AllegroSprite(sprites.at(sheetname), Rect{ pos.x, pos.y, 64, 32 });
	}
	catch (const std::out_of_range& e){
		throw CivException("AllegroSpriteFactory::CreateSprite", "Map element " + sheetname + " not existing");
	}
}
