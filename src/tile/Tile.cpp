#include "Tile.h"

using namespace std;


Tile::Tile(const BasicTerrainset& terrainset_) :
	terrainset{ terrainset_ },
	basicSpriteID{ terrainset.GetRandomBasicID() },
	resourceID{ terrainset.GetRandomResourceID() },
	sprite{ SpriteManager::Instance().GetDummy() }{
}

void Tile::UpdateSprite(uint8_t terrainNeighbourMask){
	vector<uint32_t> spriteHashes;

	terrainset.GetSpriteHashes(spriteHashes, basicSpriteID, resourceID, terrainNeighbourMask);
	sprite = SpriteManager::Instance().GetTerrainComposite(spriteHashes, terrainset.GetType());
}

void Tile::RandomizeBaseSprite(mt19937& rng){
	basicSpriteID = rng() % terrainset.GetBasicSpriteCount();
}

void Tile::RandomizeResource(mt19937& rng){
	if(static_cast<uint8_t>(rng() % 100) < terrainset.GetResourceChance())
		resourceID = rng() % terrainset.GetResourceCount();
	else
		resourceID = -1;
}

void Tile::Render(int x, int y){
	sprite->Render(x, y);
}
