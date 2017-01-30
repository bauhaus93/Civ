#include "Tile.h"

using namespace std;


Tile::Tile(const BasicTerrainset& terrainset_ ) :
	terrainset{ terrainset_ },
	basicSpriteID{ terrainset.GetRandomBasicID() },
	resourceID{ terrainset.GetRandomResourceID() },
	sprite{ &SpriteManager::Instance().GetDummy() }{
}

void Tile::UpdateSprite(uint8_t terrainNeighbourMask){
	vector<uint32_t> spriteHashes;

	terrainset.GetSpriteHashes(spriteHashes, basicSpriteID, resourceID, terrainNeighbourMask);
	sprite = &SpriteManager::Instance().GetTerrainComposite(spriteHashes, terrainset.GetType());
}

void Tile::Render(int x, int y){
	sprite->Render(x, y);
}
