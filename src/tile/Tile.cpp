#include "Tile.h"

using namespace std;


Tile::Tile(const BasicTerrainset& terrainset_ ) :
	terrainset{ terrainset_ },
	basicSpriteID{ terrainset.GetRandomBasicID() },
	resourceID{ terrainset.GetRandomResourceID() },
	terrainNeighbourMask{ 0 }{
}

void Tile::AddSprite(const Sprite& add){
	sprite->Add(add);
}

void Tile::UpdateTerrainNeighbourMask(uint8_t newMask){
	terrainNeighbourMask = newMask;
}

void Tile::CreateSprite(){
	sprite = make_unique<Sprite>(Rect{0, 0, 64, 32});

	terrainset.Draw(*sprite, basicSpriteID, resourceID, terrainNeighbourMask);
}

void Tile::Render(int x, int y){
	sprite->Render(x, y);
}
