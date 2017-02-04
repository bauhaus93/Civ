#pragma once

#include <vector>
#include <memory>
#include <functional>

#include "BasicTerrainset.h"
#include "TilesetType.h"
#include "Resource.h"
#include "engine/Sprite.h"
#include "engine/SpriteManager.h"
#include "map/Neighbour.h"
#include "common/Hash.h"

enum class Coastline{ N, E, S, W };

uint32_t GetCoastlineMask(uint8_t neighbourMask, Coastline coastline);

//TODO mabye refactor to be an extended terrainset, which overrides Draw (less work in TileFactory)

class OceanTerrainset: public BasicTerrainset{
    std::map<uint32_t, std::shared_ptr<const Sprite>>	coastline;

    void                CreateCoastline(Sprite& sprite, uint8_t neighbourMask) const;
    uint32_t            GetCoastlineHash(uint8_t neighbourMask, Coastline dir) const;
    uint32_t            GetCoastlineHash(uint8_t neighbourMask) const;

public:
                        OceanTerrainset(const std::string& name_, uint8_t resourceChance_);
                        ~OceanTerrainset() = default;

    void                AddCoastline(std::shared_ptr<Sprite> sprite, uint32_t mask);
    std::shared_ptr<Sprite>  CreateComposite(uint32_t floorHash, uint32_t resourceHash, uint8_t neighbourMask) const override;



    TilesetType         GetType() const override;
};
