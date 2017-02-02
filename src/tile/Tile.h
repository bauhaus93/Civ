#pragma once

#include <memory>
#include <vector>

#include "tileset/BasicTerrainset.h"
#include "tileset/TilesetType.h"
#include "engine/Sprite.h"
#include "engine/SpriteManager.h"
#include "Neighbour.h"



class Tile{
	const BasicTerrainset& 	terrainset;
	int						basicSpriteID;
	int 					resourceID;

    int                     x;
    int                     y;

    Tile*                   neighbour[4];
    uint8_t                 NeighbourMask;

	std::shared_ptr<const Sprite> sprite;

public:

	explicit				Tile(const BasicTerrainset& tileset_, int x_, int y_);
							Tile(const Tile& other) = delete;
							~Tile() = default;

	void                   UpdateSprite(std::vector<uint32_t>& spriteHashes, uint8_t terrainNeighbourMask);
	void                   RandomizeBaseSprite(std::mt19937& rng);
	void                   RandomizeResource(std::mt19937& rng);
	const BasicTerrainset& GetTerrainset();
	uint32_t 			   GetBasicSpriteHash() const;
	uint32_t               GetResourceSpriteHash() const;
	bool                   HasResource() const;

	void                   Render(int x, int y);
    void                   RenderRow(int startX, int startY, int maxX);

    int		               GetX() const;
    int		               GetY() const;
    bool	               IsOdd() const;

    void                   SetNeighbour(Tile *tile, int neighbour);
    Tile*                  GetNeighbour(int neighbour) const;
    void                   LinkNeighbours(Tile* tile, int neighbour);

};

inline const BasicTerrainset& Tile::GetTerrainset(){
	return terrainset;
}

inline uint32_t Tile::GetBasicSpriteHash() const{
	return terrainset.GetBasicSpriteHash(basicSpriteID);
}

inline void Tile::Render(int x, int y){
	sprite->Render(x, y);
}

inline int Node::GetX() const{
    return x;
}

inline int Node::GetY() const{
    return y;
}

inline bool	Node::IsOdd() const{
    return GetY() % 2 == 1;
}
