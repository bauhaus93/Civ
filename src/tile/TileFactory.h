#pragma once

#include <string>
#include <memory>

#include "Tile.h"
#include "TileSimple.h"
#include "TileExtended.h"
#include "Tileset.h"
#include "engine/SpriteFactory.h"
#include "engine/Sprite.h"
#include "common/Color.h"
#include "common/Point.h"
#include "exception/CivException.h"


class TileFactory{

    SpriteFactory                   spriteFactory;
    std::map<std::string, Tileset>  tilesets;

public:

            TileFactory();

    void    AddSimpleTileset(const std::string& name, unsigned int resourceChance);
    void    AddFloor(const std::string& tilesetName, const Point& pos);
    void    AddResource(const std::string& tilesetName, const Point& pos);

    int     GetTilesetCount() const;
    bool    HasTileset(const std::string& tilesetName) const;

    std::unique_ptr<Tile> CreateTile(const std::string& tilesetName) const;

};
