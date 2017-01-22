#include "BasicTerrainset.h"

using namespace std;

BasicTerrainset::BasicTerrainset(const string& name_, uint8_t resourceChance_):
    Tileset(name_),
    resourceChance{ resourceChance_ }{

}

void BasicTerrainset::AddBasicSprite(Sprite&& sprite){
    basic.push_back(move(sprite));
}

void BasicTerrainset::AddResource(Resource&& res){
    resource.push_back(move(res));
}

int BasicTerrainset::GetRandomBasicID() const{
    return common::Random(basic.size());
}
int BasicTerrainset::GetRandomResourceID() const{
    if(common::Random() < resourceChance)
        return common::Random(resource.size());
    return -1;
}

void BasicTerrainset::Draw(Sprite& sprite, int basicID, int resourceID, uint8_t neighbourMask) const{
    sprite.Add(basic.at(basicID));

    if(resourceID > -1)
        sprite.Add(resource.at(resourceID).GetSprite());
}

int BasicTerrainset::GetType() const{
    return (int)TilesetType::BASIC;
}
