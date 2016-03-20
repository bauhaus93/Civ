#pragma once

#include <map>
#include <memory>
#include <string>

#include "Tileset.h"
#include "BaseTile.h"

class TileFactory{

	std::map<std::string, std::unique_ptr<Tileset>>	tilesets;

public:

			TileFactory();
	void	AddTileset(std::unique_ptr<Tileset> tileset);

	std::unique_ptr<BaseTile> GetRandom();
};
