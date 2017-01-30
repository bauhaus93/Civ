#include "OceanTerrainset.h"

using namespace std;

OceanTerrainset::OceanTerrainset(const string& name_, uint8_t resourceChance_):
    BasicTerrainset(name_, resourceChance_){

}

void OceanTerrainset::AddCoastline(const Sprite& sprite, uint32_t mask){

    auto result = coastline.emplace(mask, sprite).second;

    if(result == false)
        throw CivException("OceanTerrainset::AddCoastline", "Neighourmask " + to_string((int) mask) + " already existing!");
}

void OceanTerrainset::GetSpriteHashes(vector<uint32_t>& spriteHashes, int basicID, int resourceID, uint8_t neighbourMask) const{
    BasicTerrainset::GetSpriteHashes(spriteHashes, basicID, resourceID, neighbourMask);

    //N, S, W, E coastlines
    uint8_t mask[] = { ((neighbourMask & static_cast<uint8_t>(Neighbour::N)) ? 0 : 2) | ((neighbourMask & static_cast<uint8_t>(Neighbour::NW)) ? 0 : 1) | ((neighbourMask & static_cast<uint8_t>(Neighbour::NE)) ? 0 : 4),
                        ((neighbourMask & static_cast<uint8_t>(Neighbour::S)) ? 0 : 2) | ((neighbourMask & static_cast<uint8_t>(Neighbour::SW)) ? 0 : 4) | ((neighbourMask & static_cast<uint8_t>(Neighbour::SE)) ? 0 : 1),
                        ((neighbourMask & static_cast<uint8_t>(Neighbour::W)) ? 0 : 2) | ((neighbourMask & static_cast<uint8_t>(Neighbour::NW)) ? 0 : 4) | ((neighbourMask & static_cast<uint8_t>(Neighbour::SW)) ? 0 : 1),
                        ((neighbourMask & static_cast<uint8_t>(Neighbour::E)) ? 0 : 2) | ((neighbourMask & static_cast<uint8_t>(Neighbour::NE)) ? 0 : 1) | ((neighbourMask & static_cast<uint8_t>(Neighbour::SE)) ? 0 : 4)};

    for(int i = 0; i < 4; i++){
        if(mask[i] != 0)
            spriteHashes.push_back(coastline.at(mask[i] << (i * 8)).get().GetHash());
        else
            spriteHashes.push_back(0);
    }
}

TilesetType OceanTerrainset::GetType() const{
    return TilesetType::OCEAN;
}
