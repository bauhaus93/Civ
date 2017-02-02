#pragma once

#include <memory>
#include <map>
#include <random>

#include "Grid.h"
#include "WorldGenerator.h"
#include "Log.h"
#include "engine/SpriteFactory.h"
#include "tile/TilesetManager.h"
#include "common/Rect.h"

class Map{

	Rect					drawField;
	TilesetManager			tilesetManager;
	Grid					grid;

	bool change;

public:
	explicit	Map(const Rect& drawField_);
				~Map() = default;

	void		Clicked(int screenX, int screenY);
	void		Render();
};
