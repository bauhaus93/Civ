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

shared_ptr<Sprite> ExtendedTerrainset::CreateComposite(uint32_t floorHash, uint32_t resourceHash, uint8_t neighbourMask) const{
    uint32_t extensionHash = GetExtensionSpriteHash(neighbourMask);
    uint32_t compositeHash = Hash(floorHash, resourceHash, extensionHash);

    assert(floorHash != 0);
    assert(extensionHash != 0);
    assert(compositeHash != 0);

    auto sprite = SpriteManager::Instance().GetElement(compositeHash);
    if(sprite == nullptr){
        sprite = make_shared<Sprite>(*SpriteManager::Instance().GetExistingElement(floorHash), Rect{ 0, 0, 64, 32 });

        sprite->Add(*SpriteManager::Instance().GetExistingElement(extensionHash));

        if(resourceHash != 0)
            sprite->Add(*SpriteManager::Instance().GetExistingElement(resourceHash));
        SpriteManager::Instance().RegisterSprite(sprite, compositeHash);
    }
    return sprite;
}

TilesetType ExtendedTerrainset::GetType() const{
    return TilesetType::EXTENDED;
}
