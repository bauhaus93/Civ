#pragma once

#include <map>
#include <memory>
#include <string>

#include "Tileset.h"

class TileFactory{

	std::map<std::string, std::unique_ptr<Tileset>>	tilesets;

public:

			TileFactory();
	void	AddTileset(std::unique_ptr<Tileset> tileset);

};
