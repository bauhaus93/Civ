#include "BasicTerrainset.h"

using namespace std;

BasicTerrainset::BasicTerrainset(const string& name_, uint8_t resourceChance_):
    Tileset(name_),
    resourceChance{ resourceChance_ }{

}

void BasicTerrainset::AddBasicSprite(shared_ptr<Sprite> sprite){
    basic.push_back(sprite);
}

void BasicTerrainset::AddResource(Resource res){
    resource.push_back(res);
}

shared_ptr<Sprite> BasicTerrainset::CreateComposite(uint32_t floorHash, uint32_t resourceHash, uint8_t neighbourMask) const{
    uint32_t compositeHash = Hash(floorHash, resourceHash);

    assert(floorHash != 0);
    assert(compositeHash != 0);

    auto sprite = SpriteManager::Instance().GetElement(compositeHash);
    if(sprite == nullptr){
        sprite = make_shared<Sprite>(*SpriteManager::Instance().GetExistingElement(floorHash), Rect{ 0, 0, 64, 32 });


        if(resourceHash != 0)
            sprite->Add(*SpriteManager::Instance().GetExistingElement(resourceHash));
        SpriteManager::Instance().RegisterSprite(sprite, compositeHash);
    }
    return sprite;
}

int BasicTerrainset::GetRandomBasicID() const{
    return common::Random(basic.size());
}

int BasicTerrainset::GetRandomResourceID() const{
    if(common::Random() < resourceChance)
        return common::Random(resource.size());
    return -1;
}

int BasicTerrainset::GetResourceChance() const{
    return resourceChance;
}

int BasicTerrainset::GetBasicSpriteCount() const{
    return basic.size();
}

int BasicTerrainset::GetResourceCount() const{
    return resource.size();
}

TilesetType BasicTerrainset::GetType() const{
    return TilesetType::BASIC;
}
