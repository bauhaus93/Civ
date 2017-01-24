#include "OceanTerrainset.h"

using namespace std;

OceanTerrainset::OceanTerrainset(const string& name_, uint8_t resourceChance_):
    BasicTerrainset(name_, resourceChance_){

}

void OceanTerrainset::AddCoastline(Sprite&& sprite, uint32_t mask){

    auto result = coastline.emplace(mask, move(sprite)).second;

    if(result == false)
        throw CivException("OceanTerrainset::AddCoastline", "Neighourmask " + to_string((int) mask) + " already existing!");
}

void OceanTerrainset::Draw(Sprite& sprite, int basicID, int resourceID, uint8_t neighbourMask) const{
    sprite.Add(basic.at(basicID));

    uint8_t northMask = (neighbourMask & (uint8_t)Neighbour::N ? 0 : 2) | (neighbourMask & (uint8_t)Neighbour::NW ? 0 : 1) | (neighbourMask & (uint8_t)Neighbour::NE ? 0 : 4);
    uint8_t southMask = (neighbourMask & (uint8_t)Neighbour::S ? 0 : 2) | (neighbourMask & (uint8_t)Neighbour::SW ? 0 : 4) | (neighbourMask & (uint8_t)Neighbour::SE ? 0 : 1);
    uint8_t westMask = (neighbourMask & (uint8_t)Neighbour::W ? 0 : 2) | (neighbourMask & (uint8_t)Neighbour::NW ? 0 : 4) | (neighbourMask & (uint8_t)Neighbour::SW ? 0 : 1);
    uint8_t eastMask = (neighbourMask & (uint8_t)Neighbour::E ? 0 : 2) | (neighbourMask & (uint8_t)Neighbour::NE ? 0 : 1) | (neighbourMask & (uint8_t)Neighbour::SE ? 0 : 4);

    if(northMask != 0)
        sprite.Add(coastline.at(northMask), Point{0, 0}, Point{16, 0});
    if(southMask != 0)
        sprite.Add(coastline.at(southMask << 8), Point{0, 0}, Point{16, 16});
    if(westMask != 0)
        sprite.Add(coastline.at(westMask << 16), Point{0, 0}, Point{0, 8});
    if(eastMask != 0)
        sprite.Add(coastline.at(eastMask << 24), Point{0, 0}, Point{32, 8});

    if(resourceID > -1)
        sprite.Add(resource.at(resourceID).GetSprite());
}

int OceanTerrainset::GetType() const{
    return BasicTerrainset::GetType() | (int)TilesetType::OCEAN;
}
