#pragma once

#include <string>
#include <memory>

#include "Tile.h"
#include "Tileset.h"
#include "Log.h"
#include "BasicTerrainset.h"
#include "ExtendedTerrainset.h"
#include "OceanTerrainset.h"
#include "engine/SpriteManager.h"
#include "engine/Sprite.h"
#include "common/Color.h"
#include "common/Point.h"
#include "common/Rect.h"
#include "exception/CivException.h"

class TilesetManager{

    SpriteManager& spriteManager;
    std::map<std::string, std::shared_ptr<Tileset>> tilesets;

    const unsigned int resourceChance;

    void LoadBasicTilesets();
    void LoadExtendedTilesets();
    void LoadOceanTileset();

    void AddTileset(const std::string& name, unsigned int resourceChance, TilesetType type);
    void AddBasicTileset(const std::string& name, unsigned int resourceChance);
    void AddExtendedTileset(const std::string& name, unsigned int resourceChance);
    void AddOceanTileset(const std::string& name, unsigned int resourceChance);
    void AddBasicSprite(const std::string& tilesetName, const Point& pos);
    void AddResource(const std::string& tilesetName, const Point& pos);
    void AddExtendedSprite(const std::string& tilesetName, const Point& pos, uint8_t neighbourMask);
    void AddCoastline(const std::string& tilesetName, const Point& pos, uint32_t mask);

public:

    explicit    TilesetManager(unsigned int resourceChance_);
    void        LoadTilesets();

    int         GetTilesetCount() const;
    bool        HasTileset(const std::string& tilesetName) const;

    std::shared_ptr<BasicTerrainset> GetTerrainset(const std::string& terrainsetName) const;

};
