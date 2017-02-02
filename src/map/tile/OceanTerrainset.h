#pragma once

#include <vector>
#include <memory>
#include <functional>

#include "BasicTerrainset.h"
#include "TilesetType.h"
#include "Resource.h"
#include "engine/Sprite.h"
#include "map/Neighbour.h"


//TODO mabye refactor to be an extended terrainset, which overrides Draw (less work in TileFactory)

class OceanTerrainset: public BasicTerrainset{
    std::map<uint32_t, std::shared_ptr<const Sprite>>	coastline;

public:
                        OceanTerrainset(const std::string& name_, uint8_t resourceChance_);
                        ~OceanTerrainset() = default;

    void                AddCoastline(std::shared_ptr<Sprite> sprite, uint32_t mask);

    void                GetSpriteHashes(std::vector<uint32_t>& hashes, int basicID, int resourceID, uint8_t neighbourMask) const override;
    TilesetType         GetType() const override;
};