#pragma once

#include <vector>
#include <map>
#include <functional>
#include <memory>

#include "BasicTerrainset.h"
#include "TilesetType.h"
#include "Resource.h"
#include "engine/Sprite.h"
#include "exception/CivException.h"



class ExtendedTerrainset: public BasicTerrainset{
    std::map<uint8_t, std::shared_ptr<const Sprite>>	extension;

public:
                ExtendedTerrainset(const std::string& name_, uint8_t resourceChance_);
                ~ExtendedTerrainset() = default;

    void        AddExtendedSprite(std::shared_ptr<Sprite> sprite, uint8_t neighbourMask);

    void        GetSpriteHashes(std::vector<uint32_t>& hashes, int basicID, int resourceID, uint8_t neighbourMask) const override;
    TilesetType GetType() const override;
};
