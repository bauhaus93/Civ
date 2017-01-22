#pragma once

#include <vector>
#include <map>

#include "engine/Sprite.h"
#include "tile/Resource.h"
#include "exception/CivException.h"
#include "BasicTerrainset.h"


class ExtendedTerrainset: public BasicTerrainset{
    std::map<uint8_t, Sprite>	extension;

public:
                ExtendedTerrainset(const std::string& name_, uint8_t resourceChance_);
                ~ExtendedTerrainset() = default;

    void        AddExtendedSprite(Sprite&& sprite, uint8_t neighbourMask);

    void        Draw(Sprite& sprite, int basicID, int resourceID, uint8_t neighbourMask) const override;
    int         GetType() const override;
};
