#include "AllegroSpriteFactory.h"



AllegroSpriteFactory::AllegroSpriteFactory(){
	al_set_new_bitmap_format(ALLEGRO_PIXEL_FORMAT_ARGB_8888);
}


AllegroSpriteFactory::~AllegroSpriteFactory(){
	sprites.clear();
}

void AllegroSpriteFactory::AddSpriteSheet(const std::string& sheetname, const std::string& filename){
	if(sprites.find(sheetname) != sprites.end())
		throw CivException("AllegroSpriteFactory::AddSpriteSheet", "Sheet \"" + sheetname + "\" already existing!");
	sprites.emplace(make_pair(sheetname, filename));
}

void AllegroSpriteFactory::MakeTransparent(const RGBColor& color){
	for (auto& iter : sprites){
		iter.second.MakeColorTransparent(color);
	}
}

std::shared_ptr<AllegroSprite> AllegroSpriteFactory::CreateSprite(const std::string& sheetname, const Rect& dim){
	try{
		return std::make_shared<AllegroSprite>(sprites.at(sheetname), dim);
	}
	catch (const std::out_of_range& e){
		throw CivException("AllegroSpriteFactory::CreateSprite", "Map element " + sheetname + " not existing");
	}
}

std::shared_ptr<AllegroSprite> AllegroSpriteFactory::CreateDiamondSprite(const std::string& sheetname, const Point& pos){
	try{
		return std::make_shared<AllegroSprite>(sprites.at(sheetname), Rect{ pos.x, pos.y, 64, 32 });
	}
	catch (const std::out_of_range& e){
		throw CivException("AllegroSpriteFactory::CreateSprite", "Map element " + sheetname + " not existing");
	}
}
