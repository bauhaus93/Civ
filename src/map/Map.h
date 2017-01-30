#pragma once

#include <memory>
#include <map>
#include <random>

#include "engine/SpriteFactory.h"
#include "tile/TileFactory.h"
#include "tileset/OceanTerrainset.h"
#include "Grid.h"
#include "WorldGenerator.h"
#include "common/Rect.h"
#include "Log.h"

#define RESOURCE_CHANCE (10)


class Map{

	Rect					drawField;
	TileFactory				tileFactory;
	Grid					grid;

	bool change;

	void		LoadTilesets();
	void 		LoadBasicTilesets();
	void 		LoadExtendedTilesets();
	void 		LoadOceanTileset();

public:
	explicit	Map(const Rect& drawField_);
				~Map();

	void		Clicked(int screenX, int screenY);
	void		Render();
};
