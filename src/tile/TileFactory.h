#pragma once

#include <string>
#include <memory>

#include "Tile.h"
#include "tileset/Tileset.h"
#include "tileset/BasicTerrainset.h"
#include "tileset/ExtendedTerrainset.h"
#include "tileset/OceanTerrainset.h"
#include "engine/SpriteFactory.h"
#include "engine/Sprite.h"
#include "common/Color.h"
#include "common/Point.h"
#include "common/Rect.h"
#include "exception/CivException.h"

class TileFactory{

    SpriteFactory                                   spriteFactory;
    std::map<std::string, std::unique_ptr<Tileset>> tilesets;

    void AddTileset(const std::string& name, unsigned int resourceChance, TilesetType type);

public:

            TileFactory();

    void    AddBasicTileset(const std::string& name, unsigned int resourceChance);
    void    AddExtendedTileset(const std::string& name, unsigned int resourceChance);
    void    AddOceanTileset(const std::string& name, unsigned int resourceChance);
    void    AddBasicSprite(const std::string& tilesetName, const Point& pos);
    void    AddResource(const std::string& tilesetName, const Point& pos);
    void    AddExtendedSprite(const std::string& tilesetName, const Point& pos, uint8_t neighbourMask);
    void    AddCoastline(const std::string& tilesetName, const Point& pos, Corner corner, uint8_t mask);

    int     GetTilesetCount() const;
    bool    HasTileset(const std::string& tilesetName) const;

    std::unique_ptr<Tile> CreateTile(const std::string& tilesetName) const;

};
