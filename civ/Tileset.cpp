#include "Tileset.h"

using namespace std;

Tileset::Tileset(const string& name_, TileType type_, unsigned int resourceChance_) :
	name{ name_ },
	type{ type_ },
	resourceChance{ resourceChance_ }{
}
