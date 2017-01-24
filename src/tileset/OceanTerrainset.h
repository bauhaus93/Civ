#pragma once

#include <vector>
#include <memory>

#include "engine/Sprite.h"
#include "tile/Resource.h"
#include "BasicTerrainset.h"
#include "map/Neighbour.h"

//TODO mabye refactor to be an extended terrainset, which overrides Draw (less work in TileFactory)

enum class Corner{
    N = 0,
    E = 1,
    S = 2,
    W = 3
};

class OceanTerrainset: public BasicTerrainset{
    std::map<uint8_t, Sprite>	coastlineNorth;   //TODO pack all into a vector or so
    std::map<uint8_t, Sprite>	coastlineEast;
    std::map<uint8_t, Sprite>	coastlineSouth;
    std::map<uint8_t, Sprite>	coastlineWest;

public:
                        OceanTerrainset(const std::string& name_, uint8_t resourceChance_);
                        ~OceanTerrainset() = default;

    void                AddCoastline(Sprite&& sprite, Corner corner, uint8_t mask);

    void                Draw(Sprite& sprite, int basicID, int resourceID, uint8_t neighbourMask) const override;
    virtual	int         GetType() const override;
};
