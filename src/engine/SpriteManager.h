#pragma once

#include <map>
#include <memory>
#include <string>

#include "SpriteFactory.h"
#include "Sprite.h"
#include "common/Rect.h"
#include "common/Color.h"
#include "common/Hash.h"
#include "exception/CivException.h"
#include "tileset/TilesetType.h"

extern const std::string TERRAIN1;
extern const std::string TERRAIN2;

/*Important: Don't mix up composite hashes with the sprite hashes
Sprite hashes are calculated by the pixels of the sprite (only used for the "basic" sprites loaded from a spritesheet)
Composite hashes are calculated by the hashes of the sprites of which the composite consists
So the composite hash of a sprite and the hash of the sprite do not match!*/

class SpriteManager{

    static SpriteManager*       instance;

    SpriteFactory               factory;
    std::map<uint32_t, Sprite>  storage;
    Sprite                      dummy;


    Sprite CreateBasicTerrainComposite(const std::vector<uint32_t>& spriteHashes);
    Sprite CreateExtendedTerrainComposite(const std::vector<uint32_t>& spriteHashes);
    Sprite CreateOceanTerrainComposite(const std::vector<uint32_t>& spriteHashes);

    SpriteManager();
    ~SpriteManager();

public:

    static void             Start();
    static void             Stop();
    static SpriteManager&   Instance();

    //void        LoadSpritesheet(const std::string& sheetname, const std::string& filename);
    //void        AddSpritesheetTransparency(RGBColor color);
    Sprite&     CreateFromSpritesheet(const std::string& sheetname, const Rect& rect);
    Sprite&     CreateDiamondFromSpritesheet(const std::string& sheetname, const Point& pos);

    Sprite&     GetTerrainComposite(const std::vector<uint32_t>& spriteHashes, TilesetType type);
    Sprite&     GetDummy();

};

inline SpriteManager& SpriteManager::Instance(){
    return *instance;
}
