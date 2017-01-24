#pragma once

#include <vector>
#include <memory>

#include "engine/Sprite.h"
#include "tile/Resource.h"
#include "BasicTerrainset.h"
#include "map/Neighbour.h"

//TODO mabye refactor to be an extended terrainset, which overrides Draw (less work in TileFactory)

class OceanTerrainset: public BasicTerrainset{
    std::map<uint32_t, Sprite>	coastline;

public:
                        OceanTerrainset(const std::string& name_, uint8_t resourceChance_);
                        ~OceanTerrainset() = default;

    void                AddCoastline(Sprite&& sprite, uint32_t mask);

    void                Draw(Sprite& sprite, int basicID, int resourceID, uint8_t neighbourMask) const override;
    virtual	int         GetType() const override;
};
