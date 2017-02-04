#include "OceanTerrainset.h"

using namespace std;

uint32_t GetCoastlineMask(uint8_t neighbourMask, Coastline coastline){
    uint32_t mask = 0;
    switch(coastline){
    case Coastline::N:
        mask |= (neighbourMask & (1 << static_cast<uint8_t>(Neighbour::NW))) ? static_cast<uint8_t>(0) : static_cast<uint8_t>(1);
        mask |= (neighbourMask & (1 << static_cast<uint8_t>(Neighbour::N))) ? static_cast<uint8_t>(0) : static_cast<uint8_t>(2);
        mask |= (neighbourMask & (1 << static_cast<uint8_t>(Neighbour::NE))) ? static_cast<uint8_t>(0) : static_cast<uint8_t>(4);
        mask <<= 0;
        break;
    case Coastline::S:
        mask |= (neighbourMask & (1 << static_cast<uint8_t>(Neighbour::SE))) ? static_cast<uint8_t>(0) : static_cast<uint8_t>(1);
        mask |= (neighbourMask & (1 << static_cast<uint8_t>(Neighbour::S))) ? static_cast<uint8_t>(0) : static_cast<uint8_t>(2);
        mask |= (neighbourMask & (1 << static_cast<uint8_t>(Neighbour::SW))) ? static_cast<uint8_t>(0) : static_cast<uint8_t>(4);
        mask <<= 8;
        break;
    case Coastline::W:
        mask |= (neighbourMask & (1 << static_cast<uint8_t>(Neighbour::SW))) ? static_cast<uint8_t>(0) : static_cast<uint8_t>(1);
        mask |= (neighbourMask & (1 << static_cast<uint8_t>(Neighbour::W))) ? static_cast<uint8_t>(0) : static_cast<uint8_t>(2);
        mask |= (neighbourMask & (1 << static_cast<uint8_t>(Neighbour::NW))) ? static_cast<uint8_t>(0) : static_cast<uint8_t>(4);
        mask <<= 16;
        break;
    case Coastline::E:
        mask |= (neighbourMask & (1 << static_cast<uint8_t>(Neighbour::NE))) ? static_cast<uint8_t>(0) : static_cast<uint8_t>(1);
        mask |= (neighbourMask & (1 << static_cast<uint8_t>(Neighbour::E))) ? static_cast<uint8_t>(0) : static_cast<uint8_t>(2);
        mask |= (neighbourMask & (1 << static_cast<uint8_t>(Neighbour::SE))) ? static_cast<uint8_t>(0) : static_cast<uint8_t>(4);
        mask <<= 24;
        break;
    default:
        assert(0);
    }
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

shared_ptr<Sprite> OceanTerrainset::CreateComposite(uint32_t floorHash, uint32_t resourceHash, uint8_t neighbourMask) const{
    uint32_t coastlineHash = GetCoastlineHash(neighbourMask);
    uint32_t compositeHash = Hash(floorHash, resourceHash, coastlineHash);

    assert(floorHash != 0);
    assert(compositeHash != 0);

    auto sprite = SpriteManager::Instance().GetElement(compositeHash);
    if(sprite == nullptr){
        sprite = make_shared<Sprite>(*SpriteManager::Instance().GetExistingElement(floorHash), Rect{ 0, 0, 64, 32 });

        if(coastlineHash != 0)
            CreateCoastline(*sprite, neighbourMask);

        if(resourceHash != 0)
            sprite->Add(*SpriteManager::Instance().GetExistingElement(resourceHash));
        SpriteManager::Instance().RegisterSprite(sprite, compositeHash);
    }
    return sprite;
}

TilesetType OceanTerrainset::GetType() const{
    return TilesetType::OCEAN;
}

uint32_t OceanTerrainset::GetCoastlineHash(uint8_t neighbourMask, Coastline dir) const{
    uint32_t mask = GetCoastlineMask(neighbourMask, dir);

    if(mask != 0){
        assert(coastline.find(mask) != coastline.end());
        return coastline.at(mask)->GetHash();
    }
    return 0;
}

uint32_t OceanTerrainset::GetCoastlineHash(uint8_t neighbourMask) const{
    if(neighbourMask == 0)
        return 0;
    return Hash(GetCoastlineHash(neighbourMask, Coastline::N),
                GetCoastlineHash(neighbourMask, Coastline::S),
                GetCoastlineHash(neighbourMask, Coastline::W),
                GetCoastlineHash(neighbourMask, Coastline::E));
}

void OceanTerrainset::CreateCoastline(Sprite& sprite, uint8_t neighbourMask) const{
    static const Coastline dir[4] = {   Coastline::N,
                                        Coastline::S,
                                        Coastline::W,
                                        Coastline::E };

    static const Point pos[4] =     {   Point{ 16, 0 },
                                        Point{ 16, 16},
                                        Point{ 0, 8},
                                        Point{ 32, 8}};

    for(int i = 0; i < 4; i++){
        uint32_t hash = GetCoastlineHash(neighbourMask, dir[i]);
        if(hash != 0)
            sprite.Add(*SpriteManager::Instance().GetExistingElement(hash), Point{ 0, 0 }, pos[i]);
    }

}
