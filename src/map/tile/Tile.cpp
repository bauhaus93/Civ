#include "Tile.h"

using namespace std;


Tile::Tile(int x_, int y_) :
	terrainset{ nullptr },
	basicSpriteID{ 0 },
	resourceID{ 0 },
    x { x_ },
    y { y_ },
    neighbour { nullptr, nullptr, nullptr, nullptr },
	sprite{ nullptr }{
}

void Tile::SetTerrainset(shared_ptr<const BasicTerrainset> terrainset_){
    terrainset = terrainset_;
}

void Tile::RandomizeBaseSprite(mt19937& rng){
	basicSpriteID = rng() % terrainset->GetBasicSpriteCount();
}

void Tile::RandomizeResource(mt19937& rng){
	if(static_cast<uint8_t>(rng() % 100) < terrainset->GetResourceChance())
		resourceID = rng() % terrainset->GetResourceCount();
	else
		resourceID = -1;
}

void Tile::Update(){

    uint8_t neighbourMask = 0;

    if(terrainset->GetType() != TilesetType::BASIC)
        neighbourMask = GetNeighbourMask();

    uint32_t floorHash = GetBasicSpriteHash();
    uint32_t resourceHash = GetResourceSpriteHash();

    sprite = terrainset->CreateComposite(floorHash, resourceHash, neighbourMask);

}



void Tile::SetNeighbour(Tile* tile, Neighbour dir){
    assert((uint8_t)dir < 4);
    neighbour[static_cast<uint8_t>(dir)] = tile;
}

Tile* Tile::GetNeighbour(Neighbour dir) const{

    switch(dir){
    case Neighbour::NE:
    case Neighbour::SE:
    case Neighbour::SW:
    case Neighbour::NW:
        return neighbour[static_cast<uint8_t>(dir)];
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
        if(GetNeighbour(Neighbour::SW))
            return GetNeighbour(Neighbour::SW)->GetNeighbour(Neighbour::NW);
        break;
    default:
        assert(0);
    }
    return nullptr;
}

void Tile::LinkNeighbours(Tile* tile, Neighbour dir){
    assert((uint8_t)dir < 4);

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

uint8_t Tile::GetNeighbourMask(){
	auto ts = GetTerrainset();
    uint8_t neighbourMask = 0;

    for(int i = 0; i < 8; i++){
        auto nb = GetNeighbour(static_cast<Neighbour>(i));
        if(nb != nullptr && nb->GetTerrainset() == ts)
            neighbourMask |= (1 << i);
    }
    return neighbourMask;
}

void Tile::RenderRow(int screenX, int screenY, int maxX){
	Tile* curr = this;

	while (screenX < maxX && curr != nullptr){
		curr->Render(screenX, screenY);
		screenX += 64;
		curr = curr->GetNeighbour(Neighbour::E);
	}
}
