#include "Tile.h"

using namespace std;


Tile::Tile(const BasicTerrainset& terrainset_, int x_, int y_) :
	terrainset{ terrainset_ },
	basicSpriteID{ terrainset.GetRandomBasicID() },
	resourceID{ terrainset.GetRandomResourceID() },
    x { x_ },
    y { y_ },
    neighbour { nullptr, nullptr, nullptr, nullptr },
    neighbourMask { 0 },
	sprite{ nullptr }{
}

void Tile::GetTerrainSpriteHashes(vector<uint32_t>& spriteHashes, uint8_t terrainNeighbourMask){
	terrainset.GetSpriteHashes(spriteHashes, basicSpriteID, resourceID, terrainNeighbourMask);
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

void Tile::Update(){
    vector<uint32_t> spriteHashes;

    terrainset.GetSpriteHashes(spriteHashes, basicSpriteID, resourceID, neighbourMask);
    sprite = SpriteManager::Instance().GetTerrainComposite(spriteHashes, terrainset.GetType());
}

void Tile::SetNeighbour(Tile* tile, Neighbour dir){
    assert(dir >= 0 && dir < 4);
    neighbour[dir] = tile;
}

Tile* Tile::GetNeighbour(Neighbour dir) const{

    switch(dir){
    case Neighbour::NE:
    case Neighbour::SE:
    case Neighbour::SW:
    case Neighbour::NW:
        return neighbour[dir];
    case Neighbour::N:
        if(GetNeighbour(Neighbour::NE) != nullptr)
            return GetNeighbour(Neighbour::NE)->GetNeighbour(Neighbour::NW);
        if(GetNeighbour(Neighbour::NW))
            return GetNeighbour(Neighbour::NW)->GetNeighbour(Neighbour::NE);
        break;
    case Neighbour::E:
        if(GetNeighbour(Neighbour::NE) != nullptr)
            return GetNeighbour(Neighbour::NE)->GetNeighbour(Neighbour::SE);
        if(GetNeighbour(Neighbour::SE))
            return GetNeighbour(Neighbour::SE)->GetNeighbour(Neighbour::NE);
        break;
    case Neighbour::S:
        if(GetNeighbour(Neighbour::SE) != nullptr)
            return GetNeighbour(Neighbour::SE)->GetNeighbour(Neighbour::SW);
        if(GetNeighbour(Neighbour::SW))
            return GetNeighbour(Neighbour::SW)->GetNeighbour(Neighbour::SE);
        break;
    case Neighbour::W:
        if(GetNeighbour(Neighbour::NW) != nullptr)
            return GetNeighbour(Neighbour::NW)->GetNeighbour(Neighbour::SW);
        if(GetNeighbour(Neighbour::SE))
            return GetNeighbour(Neighbour::SW)->GetNeighbour(Neighbour::NW);
        break;
    default:
        assert(0);
    }
    return nullptr;
}

void Tile::LinkNeighbours(Tile* tile, Neighbour dir){
    assert(dir >= 0 && dir < 4);

    SetNeighbour(tile, dir);

    switch(dir){
    case Neighbour::NE:
        tile->SetNeighbour(this, Neighbour::SW);
        break;
    case Neighbour::SE:
        tile->SetNeighbour(this, Neighbour::NW);
        break;
    case Neighbour::SW:
        tile->SetNeighbour(this, Neighbour::NE);
        break;
    case Neighbour::NW:
        tile->SetNeighbour(this, Neighbour::SE);
        break;
    default:
        assert(0);
    }
}

void Node::UpdateNeighbourMask(){
	auto& ts = GetTerrainset();

    neighbourMask = 0;

    for(int i = 0; i < 8; i++){
        if(neighbour[i] != nullptr && ts == GetNeighbour(i)->GetTerrainset())
            neighbourMask |= (1 << i);
    }
}

void Tile::RenderRow(int screenX, int screenY, int maxX){
	Tile* curr = this;

	while (screenX < maxX && curr != nullptr){
		curr->Render(screenX, screenY);
		screenX += 64;
		curr = curr->GetEast();
	}
}
