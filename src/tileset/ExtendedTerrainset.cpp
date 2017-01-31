#include "ExtendedTerrainset.h"

using namespace std;

ExtendedTerrainset::ExtendedTerrainset(const string& name_, uint8_t resourceChance_):
    BasicTerrainset(name_, resourceChance_){
}

void ExtendedTerrainset::AddExtendedSprite(shared_ptr<Sprite> sprite, uint8_t neighbourMask){
    auto result = extension.emplace(neighbourMask, sprite);
    if(result.second == false)
        throw CivException("ExtendedTerrainset::AddExtension", "Neighourmask " + to_string((int) neighbourMask) + " already existing!");
}

void ExtendedTerrainset::GetSpriteHashes(vector<uint32_t>& spriteHashes, int basicID, int resourceID, uint8_t neighbourMask) const{
    BasicTerrainset::GetSpriteHashes(spriteHashes, basicID, resourceID, neighbourMask);
    spriteHashes.push_back(extension.at(neighbourMask & 0xF)->GetHash());
}

TilesetType ExtendedTerrainset::GetType() const{
    return TilesetType::EXTENDED;
}
