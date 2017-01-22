#include "ExtendedTerrainset.h"

ExtendedTerrainset::ExtendedTerrainset(const std::string& name_, uint8_t resourceChance_):
    BasicTerrainset(name_, resourceChance_){
}

void ExtendedTerrainset::AddExtension(Sprite&& sprite, uint8_t neighbourMask){
    auto result = extension.emplace(neighbourMask, move(sprite));
    if(result.second == false)
        throw CivException("ExtendedTerrainset::AddExtension", "Neighourmask " + to_string((int) neighbourMask) + " already existing!");
}

void BasicTerrainset::Draw(Sprite& sprite, int basicID, int resourceID, uint8_t neighbourMask) const{
    sprite.Add(basic.at(basicID))
    sprite.Add(extension.at(neighbourMask));

    if(resourceID > -1)
        sprite.Add(resource.at(resourceID));
}
