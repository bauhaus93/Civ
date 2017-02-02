#include "TilesetManager.h"

using namespace std;


TilesetManager::TilesetManager(unsigned int resourceChance_):
    spriteManager{ SpriteManager::Instance() },
    resourceChance{ resourceChance_ }{
    LoadTilesets();
}

int TilesetManager::GetTilesetCount() const{
    return tilesets.size();
}

bool TilesetManager::HasTileset(const string& tilesetName) const{
    return tilesets.find(tilesetName) != tilesets.end();
}

void TilesetManager::LoadTilesets(){
    Logger::Write("Loading tilesets");
    LoadBasicTilesets();
    LoadExtendedTilesets();
    LoadOceanTileset();
    Logger::Write("Tilesets loaded");
}

void TilesetManager::LoadBasicTilesets(){
	Point pos{ 1, 1 };

	AddBasicTileset("desert", resourceChance);
	for(int i = 0; i < 4; i++){
		if(i < 2)
			AddBasicSprite("desert", pos);
		else
			AddResource("desert", pos);
		pos.x += 65;
	}

	pos.x = 1;
	pos.y += 33;
	AddBasicTileset("prairie", resourceChance);
	for(int i = 0; i < 3; i++){
		if(i == 0){
			AddBasicSprite("prairie", pos);
			pos.x += 65;
		}
		else
			AddResource("prairie", pos);
		pos.x += 65;
	}

	pos.x = 1;
	pos.y += 33;
	AddBasicTileset("grasslands", resourceChance);
	AddBasicSprite("grasslands", pos);
	AddResource("grasslands", Point{ 456, 232 });

	pos.x = 1;
	pos.y += 33 * 4;

	const string names[] = {"tundra", "arctic", "swamp"};
	for(int i = 0; i < 3; i++){
		AddBasicTileset(names[i], resourceChance);
		for(int j = 0; j < 3; j++){
			if(j == 0){
				AddBasicSprite(names[i], pos);
				pos.x += 65;
			}
			else
				AddResource(names[i], pos);
			pos.x += 65;
		}
		pos.x = 1;
		pos.y += 33;
	}
	AddBasicTileset("jungle", resourceChance);
	for(int i = 0; i < 4; i++){
		if(i < 2)
			AddBasicSprite("jungle", pos);
		else
			AddResource("jungle", pos);
		pos.x += 65;
	}
}

void TilesetManager::LoadExtendedTilesets(){
	Point pos{ 1, 133 };
	Point resourcePos{ 131, 100};
	Point fillerPos{ 1, 100 };
	static const string namesT1[] = {"forest", "hills", "mountains"};
	static const string namesT2[] = {"forest", "mountains", "hills"};

	for(int i = 0; i < 3; i++){
		AddExtendedTileset(namesT1[i], resourceChance);
		AddBasicSprite(namesT1[i], fillerPos);
		for(int j = 0; j < 2; j++)
			AddResource(namesT1[i], Point{ resourcePos.x + j * 65, resourcePos.y + i * 33});
	}

	for(uint8_t mask = 0; mask < 16; mask++){
		for(int i = 0; i < 3; i++)
			AddExtendedSprite(namesT2[i], Point{ pos.x, pos.y + i * 66}, mask);
		if(mask == 7){
			pos.x = 1;
			pos.y += 33;
		}
		else
			pos.x += 65;
	}
}

void TilesetManager::LoadOceanTileset(){
	Point pos{ 1, 331 };

	AddOceanTileset("ocean", resourceChance);
	AddBasicSprite("ocean", pos);
	pos.x += 65 * 2;

	for(int i = 0; i < 2; i++){
		AddResource("ocean", pos);
		pos.x += 65;
	}

	pos.x = 67;
	pos.y = 429;	//STD POS = 429, DEBUG = 378

	for(int i = 0; i < 4; i++){
		for(uint8_t j = 1; j < 8; j++){
			AddCoastline("ocean", pos, j << (8 * i));
			pos.x += 66;
		}
		if(i < 2){
			pos.x = 67;
			pos.y += 17;
		}
		else
			pos.x = 100;
	}
}


void TilesetManager::AddTileset(const string& name, unsigned int resourceChance_, TilesetType type){
    shared_ptr<Tileset> ts = nullptr;

    switch(type){
        case TilesetType::BASIC:
            ts = make_shared<BasicTerrainset>(name, resourceChance_);
            break;
        case TilesetType::EXTENDED:
            ts = make_shared<ExtendedTerrainset>(name, resourceChance_);
            break;
        case TilesetType::OCEAN:
            ts = make_shared<OceanTerrainset>(name, resourceChance_);
            break;
        default:
            throw CivException("TilesetManager::AddTileset", "Unknown tileset type: " + to_string((int)type));
    }

    auto result = tilesets.emplace(name, move(ts));
    if(result.second == false)
        throw CivException("TilesetManager::AddTileset", "Tileset " + name + " already existing!");
}

void TilesetManager::AddBasicTileset(const string& name, unsigned int resourceChance_){
    AddTileset(name, resourceChance, TilesetType::BASIC);
}

void TilesetManager::AddExtendedTileset(const string& name, unsigned int resourceChance_){
    AddTileset(name, resourceChance, TilesetType::EXTENDED);
}

void TilesetManager::AddOceanTileset(const string& name, unsigned int resourceChance_){
    AddTileset(name, resourceChance, TilesetType::OCEAN);
}

void TilesetManager::AddBasicSprite(const string& tilesetName, const Point& pos){
    auto iter = tilesets.find(tilesetName);
    if(iter == tilesets.end())
        throw CivException("TilesetManager::AddBasic", "Tileset " + tilesetName + " not existing!");

    auto& tileset = *iter->second;

    if( tileset.GetType() == TilesetType::BASIC ||
        tileset.GetType() == TilesetType::EXTENDED ||
        tileset.GetType() == TilesetType::OCEAN){
        auto sprite = spriteManager.CreateDiamondFromSpritesheet(TERRAIN1, pos);
        ((BasicTerrainset&)tileset).AddBasicSprite(sprite);
    }
    else
        throw CivException("TilesetManager::AddBasic", "Tileset " + tilesetName + " is no basic terrainset!");
}

void TilesetManager::AddResource(const string& tilesetName, const Point& pos){
    auto iter = tilesets.find(tilesetName);
    if(iter == tilesets.end())
        throw CivException("TilesetManager::AddResource", "Tileset " + tilesetName + " not existing!");

    auto& tileset = *iter->second;

    if( tileset.GetType() == TilesetType::BASIC ||
        tileset.GetType() == TilesetType::EXTENDED ||
        tileset.GetType() == TilesetType::OCEAN){
        auto sprite = spriteManager.CreateDiamondFromSpritesheet(TERRAIN1, pos);
        Resource resource{ sprite };
        ((BasicTerrainset&)tileset).AddResource(resource);
    }
    else
        throw CivException("TilesetManager::AddResource", "Tileset " + tilesetName + " is no basic terrainset!");

}

void TilesetManager::AddExtendedSprite(const string& tilesetName, const Point& pos, uint8_t neighbourMask){
    auto iter = tilesets.find(tilesetName);
    if(iter == tilesets.end())
        throw CivException("TilesetManager::AddExtendedSprite", "Tileset " + tilesetName + " not existing!");

    auto& tileset = *iter->second;

    if(tileset.GetType() == TilesetType::EXTENDED){
        auto sprite = spriteManager.CreateDiamondFromSpritesheet(TERRAIN2, pos);
        ((ExtendedTerrainset&)tileset).AddExtendedSprite(sprite, neighbourMask);
    }
    else
        throw CivException("TilesetManager::AddExtendedSprite", "Tileset " + tilesetName + " is no extended terrainset!");
}

void TilesetManager::AddCoastline(const string& tilesetName, const Point& pos, uint32_t mask){
    auto iter = tilesets.find(tilesetName);
    if(iter == tilesets.end())
        throw CivException("TilesetManager::AddCoastline", "Tileset " + tilesetName + " not existing!");

    auto& tileset = *iter->second;

    if(tileset.GetType() == TilesetType::OCEAN){
        auto sprite = spriteManager.CreateFromSpritesheet(TERRAIN2, Rect{ pos, 32, 16});
        ((OceanTerrainset&)tileset).AddCoastline(sprite, mask);
    }
    else
        throw CivException("TilesetManager::AddCoastline", "Tileset " + tilesetName + " is no ocean terrainset!");
}


shared_ptr<BasicTerrainset> TilesetManager::GetTerrainset(const std::string& terrainsetName) const{
    auto iter = tilesets.find(terrainsetName);
    if(iter == tilesets.end())
        throw CivException("TilesetManager::CreateTile", "Tileset " + terrainsetName + " not existing!");
    auto tileset = iter->second;

    if( tileset->GetType() == TilesetType::BASIC ||
        tileset->GetType() == TilesetType::EXTENDED ||
        tileset->GetType() == TilesetType::OCEAN){
        return static_pointer_cast<BasicTerrainset>(tileset);
    }

    throw CivException("TilesetManager::CreateTile", "Tileset " + terrainsetName + " is not a terrain set!");

}
