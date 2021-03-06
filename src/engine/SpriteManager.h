#pragma once

#include <map>
#include <memory>
#include <string>
#include <cassert>
#include <algorithm>

#include "SpriteFactory.h"
#include "Sprite.h"
#include "common/Rect.h"
#include "common/Color.h"
#include "common/Hash.h"
#include "exception/CivException.h"
#include "map/tile/TilesetType.h"

extern const std::string TERRAIN1;
extern const std::string TERRAIN2;

/*Important: Don't mix up composite hashes with the sprite hashes
Sprite hashes are calculated by the pixels of the sprite (only used for the "basic" sprites loaded from a spritesheet)
Composite hashes are calculated by the hashes of the sprites of which the composite consists
So the composite hash of a sprite and the hash of the sprite do not match!*/

class SpriteManager{

    static SpriteManager*                       instance;

    SpriteFactory                               factory;
    std::shared_ptr<Sprite>                     ditherMask;
    std::map<uint32_t, std::weak_ptr<Sprite>>   storage;

    SpriteManager();
    ~SpriteManager();

public:

    static void                 Start();
    static void                 Stop();
    static SpriteManager&       Instance();

    std::shared_ptr<Sprite>     GetElement(uint32_t hash);
    std::shared_ptr<Sprite>     GetExistingElement(uint32_t hash);
    bool                        RegisterSprite(std::shared_ptr<Sprite> sprite, uint32_t hash);

    int                         ClearUnneeded();

    std::shared_ptr<Sprite>     CreateFromSpritesheet(const std::string& sheetname, const Rect& rect);
    std::shared_ptr<Sprite>     CreateDiamondFromSpritesheet(const std::string& sheetname, const Point& pos);

    int                         GetStorageSize() const;
    void                        PrintStatistics() const;

};

inline SpriteManager& SpriteManager::Instance(){
    return *instance;
}
