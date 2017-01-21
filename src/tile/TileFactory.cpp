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

void TileFactory::AddTileset(const string& name, unsigned int resourceChance, bool simple){
    auto result = tilesets.emplace(name, Tileset{name, resourceChance, simple});
    if(result.second == false)
        throw CivException("TileFactory::AddSimpleTileset", "Tilset " + name + " already existing!");
}

void TileFactory::AddSimpleTileset(const string& name, unsigned int resourceChance){
    AddTileset(name, resourceChance, true);
}

void TileFactory::AddExtendedTileset(const string& name, unsigned int resourceChance){
    AddTileset(name, resourceChance, false);
}

void TileFactory::AddFloor(const string& tilesetName, const Point& pos){
    auto iter = tilesets.find(tilesetName);
    if(iter == tilesets.end())
        throw CivException("TileFactory::AddFloor", "Tileset " + tilesetName + " not existing!");

    auto& tileset = iter->second;
    auto sprite = spriteFactory.CreateDiamondSprite(TERRAIN1, pos);
    tileset.AddFloor(move(sprite));
}

void TileFactory::AddResource(const string& tilesetName, const Point& pos){
    auto iter = tilesets.find(tilesetName);
    if(iter == tilesets.end())
        throw CivException("TileFactory::AddResource", "Tileset " + tilesetName + " not existing!");

    auto& tileset = iter->second;
    auto sprite = spriteFactory.CreateDiamondSprite(TERRAIN1, pos);
    auto resource{move(sprite)};
    tileset.AddResource(move(resource));
}

void TileFactory::AddExtension(const string& tilesetName, const Point& pos, uint8_t neighbourMask){
    AddExtension(tilesetName, Rect{ pos, 64, 32 }, neighbourMask);
}

void TileFactory::AddExtension(const string& tilesetName, const Rect& dim, uint8_t neighbourMask){
    auto iter = tilesets.find(tilesetName);
    if(iter == tilesets.end())
        throw CivException("TileFactory::AddExtension", "Tileset " + tilesetName + " not existing!");
    auto& tileset = iter->second;

    if(tileset.IsSimple())
        throw CivException("TileFactory::AddExtension", "Tileset " + tilesetName + " is simple, but must be extended!");

    auto sprite = spriteFactory.CreateSprite(TERRAIN2, dim);
    tileset.AddExtension(move(sprite), neighbourMask);
}

unique_ptr<Tile> TileFactory::CreateTile(const std::string& tilesetName) const{
    auto iter = tilesets.find(tilesetName);
    if(iter == tilesets.end())
        throw CivException("TileFactory::CreateTile", "Tileset " + tilesetName + " not existing!");
    auto& tileset = iter->second;
    if(tileset.IsSimple())
        return make_unique<TileSimple>(tileset);
    return make_unique<TileExtended>(tileset);
}
