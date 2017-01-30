#pragma once

#include <vector>
#include <string>
#include <functional>

#include "common/Common.h"
#include "engine/Sprite.h"
#include "tile/Resource.h"
#include "Tileset.h"
#include "TilesetType.h"

class BasicTerrainset: public Tileset{

    uint8_t                 resourceChance;

protected:
    std::vector<std::reference_wrapper<const Sprite>>	basic;
	std::vector<Resource>	resource;

public:
                        BasicTerrainset(const std::string& name_, uint8_t resourceChance_);
    virtual             ~BasicTerrainset() = default;

    void                AddBasicSprite(const Sprite& sprite);
    void                AddResource(Resource res);
    int                 GetRandomBasicID() const;
    int                 GetRandomResourceID() const;

    virtual void        GetSpriteHashes(std::vector<uint32_t>& hashes, int basicID, int resourceID, uint8_t neighbourMask) const;
    virtual TilesetType GetType() const override;
};
