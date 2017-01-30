#pragma once

#include <vector>
#include <memory>
#include <functional>

#include "engine/Sprite.h"
#include "tile/Resource.h"
#include "BasicTerrainset.h"
#include "map/Neighbour.h"
#include "TilesetType.h"

//TODO mabye refactor to be an extended terrainset, which overrides Draw (less work in TileFactory)

class OceanTerrainset: public BasicTerrainset{
    std::map<uint32_t, std::reference_wrapper<const Sprite>>	coastline;

public:
                        OceanTerrainset(const std::string& name_, uint8_t resourceChance_);
                        ~OceanTerrainset() = default;

    void                AddCoastline(const Sprite& sprite, uint32_t mask);

    void                GetSpriteHashes(std::vector<uint32_t>& hashes, int basicID, int resourceID, uint8_t neighbourMask) const override;
    TilesetType         GetType() const override;
};
