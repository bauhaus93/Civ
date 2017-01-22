#include "OceanTerrainset.h"

using namespace std;

OceanTerrainset::OceanTerrainset(const string& name_, uint8_t resourceChance_):
    BasicTerrainset(name_, resourceChance_){
}

void OceanTerrainset::AddCoastline(Sprite&& sprite, uint8_t neighbourMask){
    auto result = coastline.emplace(neighbourMask, move(sprite));
    if(result.second == false)
        throw CivException("OceanTerrainset::AddCoastline", "Neighourmask " + to_string((int) neighbourMask) + " already existing!");
}

void OceanTerrainset::Draw(Sprite& sprite, int basicID, int resourceID, uint8_t neighbourMask) const{
    sprite.Add(basic.at(basicID));

    //TODO make coastline stuff

    if(resourceID > -1)
        sprite.Add(resource.at(resourceID).GetSprite());
}

int OceanTerrainset::GetType() const{
    return BasicTerrainset::GetType() | (int)TilesetType::OCEAN;
}
