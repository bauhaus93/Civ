#include "OceanTerrainset.h"

using namespace std;

OceanTerrainset::OceanTerrainset(const string& name_, uint8_t resourceChance_):
    BasicTerrainset(name_, resourceChance_){

}

void OceanTerrainset::AddCoastline(Sprite&& sprite, Corner corner, uint8_t mask){

    bool result = false;
    switch(corner){
        case Corner::N:
            result = coastlineNorth.emplace(mask, move(sprite)).second;
            break;
        case Corner::E:
            result = coastlineEast.emplace(mask, move(sprite)).second;
            break;
        case Corner::S:
            result = coastlineSouth.emplace(mask, move(sprite)).second;
            break;
        case Corner::W:
            result = coastlineWest.emplace(mask, move(sprite)).second;
            break;
        default:
            throw CivException("OceanTerrainset::AddCoastline", "Unknown case for Corner: " + to_string(int(corner)));
    }
    if(result == false)
        throw CivException("OceanTerrainset::AddCoastline", "Neighourmask " + to_string((int) mask) + " already existing!");
}

void OceanTerrainset::Draw(Sprite& sprite, int basicID, int resourceID, uint8_t neighbourMask) const{
    sprite.Add(basic.at(basicID));

    uint8_t northCorner = (neighbourMask & (uint8_t)Neighbour::N ? 2 : 0) | ((neighbourMask & (uint8_t)Neighbour::NW ? 1 : 0)) | ((neighbourMask & (uint8_t)Neighbour::NE ? 4 : 0));

    if(northCorner != 0)
        sprite.Add(coastlineNorth.at(northCorner), Rect{24, 0, 32, 16});


    if(resourceID > -1)
        sprite.Add(resource.at(resourceID).GetSprite());
}

int OceanTerrainset::GetType() const{
    return BasicTerrainset::GetType() | (int)TilesetType::OCEAN;
}
