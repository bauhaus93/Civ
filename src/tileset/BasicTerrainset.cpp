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

int BasicTerrainset::GetRandomBasicID() const{
    return common::Random(basic.size());
}
int BasicTerrainset::GetRandomResourceID() const{
    if(common::Random() < resourceChance)
        return common::Random(resource.size());
    return -1;
}

void BasicTerrainset::GetSpriteHashes(vector<uint32_t>& hashes, int basicID, int resourceID, uint8_t neighbourMask) const{
    hashes.push_back(basic.at(basicID)->GetHash());

    if(resourceID > -1)
        hashes.push_back(resource.at(resourceID).GetSprite()->GetHash());
    else
        hashes.push_back(0);
}

TilesetType BasicTerrainset::GetType() const{
    return TilesetType::BASIC;
}
