#pragma once

#include <vector>

#include "engine/Sprite.h"
#include "tile/Resource.h"


class OceanTerrainset: public BasicTerrainset{
    std::map<uint8_t, Sprite>	coastline;

public:
            OceanTerrainset(const std::string& name_, uint8_t resourceChance_);
            ~OceanTerrainset();

    void    AddCoastline(Sprite&& sprite, uint8_t neighbourMask);

    void    Draw(Sprite& sprite, int basicID, int resourceID, uint8_t neighbourMask) const override;
};
