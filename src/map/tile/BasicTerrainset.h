#pragma once

#include <vector>
#include <string>
#include <functional>
#include <memory>

#include "Resource.h"
#include "Tileset.h"
#include "TilesetType.h"
#include "common/Common.h"
#include "engine/Sprite.h"
#include "engine/SpriteManager.h"
#include "common/Hash.h"

class BasicTerrainset: public Tileset{

    uint8_t                 resourceChance;

protected:
    std::vector<std::shared_ptr<const Sprite>>	basic;
	std::vector<Resource>	resource;

public:
                        BasicTerrainset(const std::string& name_, uint8_t resourceChance_);
    virtual             ~BasicTerrainset() = default;

    void                AddBasicSprite(std::shared_ptr<Sprite> sprite);
    void                AddResource(Resource res);
    virtual std::shared_ptr<Sprite>  CreateComposite(uint32_t floorHash, uint32_t resourceHash, uint8_t neighbourMask) const;
    int                 GetRandomBasicID() const;
    int                 GetRandomResourceID() const;
    int                 GetBasicSpriteCount() const;
    int                 GetResourceCount() const;
    int                 GetResourceChance() const;
    uint32_t            GetBasicSpriteHash(int basicID) const;
    uint32_t            GetResourceSpriteHash(int resourceID) const;



    virtual TilesetType GetType() const override;
};

inline uint32_t BasicTerrainset::GetBasicSpriteHash(int basicID) const{
    assert(basicID >= 0 && static_cast<size_t>(basicID) < basic.size());
    return basic[basicID]->GetHash();
}

inline uint32_t BasicTerrainset::GetResourceSpriteHash(int resourceID) const{
    assert(resourceID >= 0 && static_cast<size_t>(resourceID) < resource.size());
    return resource[resourceID].GetSprite()->GetHash();
}
