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
    int                 GetRandomBasicID() const;
    int                 GetRandomResourceID() const;
    int                 GetBasicSpriteCount() const;
    int                 GetResourceCount() const;
    int                 GetResourceChance() const;
    uint32_t            GetBasicSpriteHash(int basicID) const;

    virtual void        GetSpriteHashes(std::vector<uint32_t>& hashes, int basicID, int resourceID, uint8_t neighbourMask) const;
    virtual TilesetType GetType() const override;
};

inline uint32_t BasicTerrainset::GetBasicSpriteHash(int basicID) const{
    assert(basicID >= 0 && static_cast<size_t>(basicID) < basic.size());
    return basic[basicID]->GetHash();
}
