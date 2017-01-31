#include "TileFactory.h"

using namespace std;


TileFactory::TileFactory():
    spriteManager{ SpriteManager::Instance() }{

}

int TileFactory::GetTilesetCount() const{
    return tilesets.size();
}

bool TileFactory::HasTileset(const string& tilesetName) const{
    return tilesets.find(tilesetName) != tilesets.end();
}

void TileFactory::AddTileset(const string& name, unsigned int resourceChance, TilesetType type){
    unique_ptr<Tileset> ts = nullptr;

    switch(type){
        case TilesetType::BASIC:
            ts = make_unique<BasicTerrainset>(name, resourceChance);
            break;
        case TilesetType::EXTENDED:
            ts = make_unique<ExtendedTerrainset>(name, resourceChance);
            break;
        case TilesetType::OCEAN:
            ts = make_unique<OceanTerrainset>(name, resourceChance);
            break;
        default:
            throw CivException("TileFactory::AddTileset", "Unknown tileset type: " + to_string((int)type));
    }

    auto result = tilesets.emplace(name, move(ts));
    if(result.second == false)
        throw CivException("TileFactory::AddTileset", "Tileset " + name + " already existing!");
}

void TileFactory::AddBasicTileset(const string& name, unsigned int resourceChance){
    AddTileset(name, resourceChance, TilesetType::BASIC);
}

void TileFactory::AddExtendedTileset(const string& name, unsigned int resourceChance){
    AddTileset(name, resourceChance, TilesetType::EXTENDED);
}

void TileFactory::AddOceanTileset(const string& name, unsigned int resourceChance){
    AddTileset(name, resourceChance, TilesetType::OCEAN);
}

void TileFactory::AddBasicSprite(const string& tilesetName, const Point& pos){
    auto iter = tilesets.find(tilesetName);
    if(iter == tilesets.end())
        throw CivException("TileFactory::AddBasic", "Tileset " + tilesetName + " not existing!");

    auto& tileset = *iter->second;

    if( tileset.GetType() == TilesetType::BASIC ||
        tileset.GetType() == TilesetType::EXTENDED ||
        tileset.GetType() == TilesetType::OCEAN){
        auto sprite = spriteManager.CreateDiamondFromSpritesheet(TERRAIN1, pos);
        ((BasicTerrainset&)tileset).AddBasicSprite(sprite);
    }
    else
        throw CivException("TileFactory::AddBasic", "Tileset " + tilesetName + " is no basic terrainset!");
}

void TileFactory::AddResource(const string& tilesetName, const Point& pos){
    auto iter = tilesets.find(tilesetName);
    if(iter == tilesets.end())
        throw CivException("TileFactory::AddResource", "Tileset " + tilesetName + " not existing!");

    auto& tileset = *iter->second;

    if( tileset.GetType() == TilesetType::BASIC ||
        tileset.GetType() == TilesetType::EXTENDED ||
        tileset.GetType() == TilesetType::OCEAN){
        auto sprite = spriteManager.CreateDiamondFromSpritesheet(TERRAIN1, pos);
        Resource resource{ sprite };
        ((BasicTerrainset&)tileset).AddResource(resource);
    }
    else
        throw CivException("TileFactory::AddResource", "Tileset " + tilesetName + " is no basic terrainset!");

}

void TileFactory::AddExtendedSprite(const string& tilesetName, const Point& pos, uint8_t neighbourMask){
    auto iter = tilesets.find(tilesetName);
    if(iter == tilesets.end())
        throw CivException("TileFactory::AddExtendedSprite", "Tileset " + tilesetName + " not existing!");

    auto& tileset = *iter->second;

    if(tileset.GetType() == TilesetType::EXTENDED){
        auto sprite = spriteManager.CreateDiamondFromSpritesheet(TERRAIN2, pos);
        ((ExtendedTerrainset&)tileset).AddExtendedSprite(sprite, neighbourMask);
    }
    else
        throw CivException("TileFactory::AddExtendedSprite", "Tileset " + tilesetName + " is no extended terrainset!");
}

void TileFactory::AddCoastline(const string& tilesetName, const Point& pos, uint32_t mask){
    auto iter = tilesets.find(tilesetName);
    if(iter == tilesets.end())
        throw CivException("TileFactory::AddCoastline", "Tileset " + tilesetName + " not existing!");

    auto& tileset = *iter->second;

    if(tileset.GetType() == TilesetType::OCEAN){
        auto sprite = spriteManager.CreateFromSpritesheet(TERRAIN2, Rect{ pos, 32, 16});
        ((OceanTerrainset&)tileset).AddCoastline(sprite, mask);
    }
    else
        throw CivException("TileFactory::AddCoastline", "Tileset " + tilesetName + " is no ocean terrainset!");
}


unique_ptr<Tile> TileFactory::CreateTile(const std::string& terrainsetName) const{
    auto iter = tilesets.find(terrainsetName);
    if(iter == tilesets.end())
        throw CivException("TileFactory::CreateTile", "Tileset " + terrainsetName + " not existing!");
    auto& tileset = *iter->second;

    if( tileset.GetType() == TilesetType::BASIC ||
        tileset.GetType() == TilesetType::EXTENDED ||
        tileset.GetType() == TilesetType::OCEAN){
        return make_unique<Tile>((BasicTerrainset&)tileset);
    }
    else
        throw CivException("TileFactory::CreateTile", "Tileset " + terrainsetName + " is not a terrain set!");

}
