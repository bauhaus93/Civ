#pragma once

#include <vector>
#include <map>
#include <functional>

#include "engine/Sprite.h"
#include "tile/Resource.h"
#include "exception/CivException.h"
#include "BasicTerrainset.h"
#include "TilesetType.h"


class ExtendedTerrainset: public BasicTerrainset{
    std::map<uint8_t, std::reference_wrapper<const Sprite>>	extension;

public:
                ExtendedTerrainset(const std::string& name_, uint8_t resourceChance_);
                ~ExtendedTerrainset() = default;

    void        AddExtendedSprite(const Sprite& sprite, uint8_t neighbourMask);

    void        GetSpriteHashes(std::vector<uint32_t>& hashes, int basicID, int resourceID, uint8_t neighbourMask) const override;
    TilesetType GetType() const override;
};
