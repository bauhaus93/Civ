#pragma once

#include <string>
#include <vector>
#include <memory>
#include <algorithm>

#include "Tileset.h"
#include "Tile.h"
#include "Sprite.h"

class TilesetSimple :
	public Tileset{

	std::vector<std::unique_ptr<Sprite>>	floor;
	std::vector<std::unique_ptr<Sprite>>	resource;


public:
	TilesetSimple(const std::string& name_, TileType type_, unsigned int resourceChance_);
	~TilesetSimple(void);

	void AddFloor(std::unique_ptr<Sprite> sprite){ floor.push_back(move(sprite)); };
	void AddResource(std::unique_ptr<Sprite> sprite){ resource.push_back(move(sprite)); };

	virtual std::unique_ptr<Tile> CreateTile(void) override;
	virtual void CreateTileSprite(Tile& tile) override;
};
