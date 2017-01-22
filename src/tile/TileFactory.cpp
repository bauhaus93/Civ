#include "TileFactory.h"

using namespace std;

const string TERRAIN1{"terrain1"};
const string TERRAIN2{"terrain2"};
const string TERRAIN1PATH{"bmp/TERRAIN1.bmp"};
const string TERRAIN2PATH{"bmp/TERRAIN2.bmp"};

TileFactory::TileFactory(){
    spriteFactory.AddSpriteSheet(TERRAIN1PATH, TERRAIN1);
	spriteFactory.AddSpriteSheet(TERRAIN2PATH, TERRAIN2);
	spriteFactory.MakeTransparent(RGBColor{ 0x87, 0x87, 0x87 });
	spriteFactory.MakeTransparent(RGBColor{ 0xFF, 0x00, 0xFF });
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

    if(tileset.GetType() & (int)TilesetType::BASIC){
        auto sprite = spriteFactory.CreateDiamondSprite(TERRAIN1, pos);
        ((BasicTerrainset&)tileset).AddBasicSprite(move(sprite));
    }
    else
        throw CivException("TileFactory::AddBasic", "Tileset " + tilesetName + " is no basic terrainset!");
}

void TileFactory::AddResource(const string& tilesetName, const Point& pos){
    auto iter = tilesets.find(tilesetName);
    if(iter == tilesets.end())
        throw CivException("TileFactory::AddResource", "Tileset " + tilesetName + " not existing!");

    auto& tileset = *iter->second;

    if(tileset.GetType() & (int)TilesetType::BASIC){
        auto sprite = spriteFactory.CreateDiamondSprite(TERRAIN1, pos);
        auto resource{move(sprite)};
        ((BasicTerrainset&)tileset).AddResource(move(resource));
    }
    else
        throw CivException("TileFactory::AddResource", "Tileset " + tilesetName + " is no basic terrainset!");

}

void TileFactory::AddExtendedSprite(const string& tilesetName, const Point& pos, uint8_t neighbourMask){
    auto iter = tilesets.find(tilesetName);
    if(iter == tilesets.end())
        throw CivException("TileFactory::AddExtendedSprite", "Tileset " + tilesetName + " not existing!");

    auto& tileset = *iter->second;

    if(tileset.GetType() & (int)TilesetType::EXTENDED){
        auto sprite = spriteFactory.CreateDiamondSprite(TERRAIN2, pos);
        ((ExtendedTerrainset&)tileset).AddExtendedSprite(move(sprite), neighbourMask);
    }
    else
        throw CivException("TileFactory::AddExtendedSprite", "Tileset " + tilesetName + " is no extended terrainset!");
}

void TileFactory::AddCoastline(const string& tilesetName, const Point& pos, Corner corner, uint8_t mask){
    auto iter = tilesets.find(tilesetName);
    if(iter == tilesets.end())
        throw CivException("TileFactory::AddCoastline", "Tileset " + tilesetName + " not existing!");

    auto& tileset = *iter->second;

    if(tileset.GetType() & (int)TilesetType::OCEAN){
        auto sprite = spriteFactory.CreateSprite(TERRAIN2, Rect{pos, 32, 16});
        ((OceanTerrainset&)tileset).AddCoastline(move(sprite), corner, mask);
    }
    else
        throw CivException("TileFactory::AddCoastline", "Tileset " + tilesetName + " is no ocean terrainset!");
}


unique_ptr<Tile> TileFactory::CreateTile(const std::string& terrainsetName) const{
    auto iter = tilesets.find(terrainsetName);
    if(iter == tilesets.end())
        throw CivException("TileFactory::CreateTile", "Tileset " + terrainsetName + " not existing!");
    auto& tileset = *iter->second;

    if(tileset.GetType() & (int)TilesetType::BASIC){
        return make_unique<Tile>((BasicTerrainset&)tileset);
    }
    else
        throw CivException("TileFactory::CreateTile", "Tileset " + terrainsetName + " is not a terrain set!");

}
