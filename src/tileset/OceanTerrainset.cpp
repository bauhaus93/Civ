#include "OceanTerrainset.h"

using namespace std;

uint8_t GetNorthernCoastline(uint8_t neighbourMask){
    uint8_t mask = 0;
    mask |= (neighbourMask & (1 << static_cast<uint8_t>(Neighbour::N))) ? static_cast<uint8_t>(0) : static_cast<uint8_t>(2);
    mask |= (neighbourMask & (1 << static_cast<uint8_t>(Neighbour::NW))) ? static_cast<uint8_t>(0) : static_cast<uint8_t>(1);
    mask |= (neighbourMask & (1 << static_cast<uint8_t>(Neighbour::NE))) ? static_cast<uint8_t>(0) : static_cast<uint8_t>(4);
    return mask;
}

uint8_t GetSouthernCoastline(uint8_t neighbourMask){
    uint8_t mask = 0;
    mask |= (neighbourMask & (1 << static_cast<uint8_t>(Neighbour::S))) ? static_cast<uint8_t>(0) : static_cast<uint8_t>(2);
    mask |= (neighbourMask & (1 << static_cast<uint8_t>(Neighbour::SW))) ? static_cast<uint8_t>(0) : static_cast<uint8_t>(4);
    mask |= (neighbourMask & (1 << static_cast<uint8_t>(Neighbour::SE))) ? static_cast<uint8_t>(0) : static_cast<uint8_t>(1);
    return mask;
}

uint8_t GetWesternCoastline(uint8_t neighbourMask){
    uint8_t mask = 0;
    mask |= (neighbourMask & (1 << static_cast<uint8_t>(Neighbour::W))) ? static_cast<uint8_t>(0) : static_cast<uint8_t>(2);
    mask |= (neighbourMask & (1 << static_cast<uint8_t>(Neighbour::NW))) ? static_cast<uint8_t>(0) : static_cast<uint8_t>(4);
    mask |= (neighbourMask & (1 << static_cast<uint8_t>(Neighbour::SW))) ? static_cast<uint8_t>(0) : static_cast<uint8_t>(1);
    return mask;
}

uint8_t GetEasternCoastline(uint8_t neighbourMask){
    uint8_t mask = 0;
    mask |= (neighbourMask & (1 << static_cast<uint8_t>(Neighbour::E))) ? static_cast<uint8_t>(0) : static_cast<uint8_t>(2);
    mask |= (neighbourMask & (1 << static_cast<uint8_t>(Neighbour::NE))) ? static_cast<uint8_t>(0) : static_cast<uint8_t>(1);
    mask |= (neighbourMask & (1 << static_cast<uint8_t>(Neighbour::SE))) ? static_cast<uint8_t>(0) : static_cast<uint8_t>(4);
    return mask;
}

OceanTerrainset::OceanTerrainset(const string& name_, uint8_t resourceChance_):
    BasicTerrainset(name_, resourceChance_){

}

void OceanTerrainset::AddCoastline(shared_ptr<Sprite> sprite, uint32_t mask){
    auto result = coastline.emplace(mask, sprite).second;

    if(result == false)
        throw CivException("OceanTerrainset::AddCoastline", "Neighourmask " + to_string((int) mask) + " already existing!");
}

void OceanTerrainset::GetSpriteHashes(vector<uint32_t>& spriteHashes, int basicID, int resourceID, uint8_t neighbourMask) const{
    BasicTerrainset::GetSpriteHashes(spriteHashes, basicID, resourceID, neighbourMask);


    //N, S, W, E coastlines
    uint8_t mask[] = {  GetNorthernCoastline(neighbourMask),
                        GetSouthernCoastline(neighbourMask),
                        GetWesternCoastline(neighbourMask),
                        GetEasternCoastline(neighbourMask)};


    for(int i = 0; i < 4; i++){
        if(mask[i] != 0)
            spriteHashes.push_back(coastline.at(mask[i] << (i * 8))->GetHash());
        else
            spriteHashes.push_back(0);
    }

}

TilesetType OceanTerrainset::GetType() const{
    return TilesetType::OCEAN;
}
