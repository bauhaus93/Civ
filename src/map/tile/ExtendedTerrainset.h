#pragma once

#include <vector>
#include <map>
#include <functional>
#include <memory>

#include "BasicTerrainset.h"
#include "TilesetType.h"
#include "Resource.h"
#include "engine/Sprite.h"
#include "engine/SpriteManager.h"
#include "exception/CivException.h"
#include "common/Hash.h"




class ExtendedTerrainset: public BasicTerrainset{
    std::map<uint8_t, std::shared_ptr<const Sprite>>	extension;

    uint32_t    GetExtensionSpriteHash(uint8_t neighbourMask) const;

public:
                ExtendedTerrainset(const std::string& name_, uint8_t resourceChance_);
                ~ExtendedTerrainset() = default;

    void        AddExtendedSprite(std::shared_ptr<Sprite> sprite, uint8_t neighbourMask);

    std::shared_ptr<Sprite>  CreateComposite(uint32_t floorHash, uint32_t resourceHash, uint8_t neighbourMask) const override;

    TilesetType GetType() const override;
};

inline uint32_t ExtendedTerrainset::GetExtensionSpriteHash(uint8_t neighbourMask) const{
    assert(extension.find(neighbourMask & 0xF) != extension.end());
    return extension.at(neighbourMask & 0xF)->GetHash();
}
