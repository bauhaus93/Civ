#pragma once

#include <vector>
#include <string>

#include "common/Common.h"
#include "engine/Sprite.h"
#include "tile/Resource.h"
#include "Tileset.h"

class BasicTerrainset: public Tileset{

    uint8_t                 resourceChance;

protected:
    std::vector<Sprite>		basic;
	std::vector<Resource>	resource;

public:
                        BasicTerrainset(const std::string& name_, uint8_t resourceChance_);
    virtual             ~BasicTerrainset() = default;

    void                AddBasicSprite(Sprite&& sprite);
    void                AddResource(Resource&& res);
    int                 GetRandomBasicID() const;
    int                 GetRandomResourceID() const;

    virtual void        Draw(Sprite& sprite, int basicID, int resourceID, uint8_t neighbourMask) const;
    virtual int         GetType() const override;
};
