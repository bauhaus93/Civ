#include "WorldGenerator.h"

/* This makes good landmass/ocean noise for now:
noise.GetOctavedNoise(node->GetX(), node->GetY(), 6, 0.2, 0.02) > 0.33 || noise.GetOctavedNoise(node->GetX(), node->GetY(), 3, 0.5, 0.1) > 0.33)
*/

using namespace std;

static unique_ptr<Tile> CreateTile(const Tileset& tileset);

WorldGenerator::WorldGenerator(){
}


WorldGenerator::~WorldGenerator(){
}

void WorldGenerator::Generate(Grid & grid, std::vector<Tileset>& tilesets){
	SimplexNoise noise{};
	GridTraversal g{ grid };

	while (g.HasNext()){
		auto node = g.Next();

		if(noise.GetOctavedNoise(node->GetX(), node->GetY(), 6, 0.2, 0.02) > 0.33 || noise.GetOctavedNoise(node->GetX(), node->GetY(), 3, 0.5, 0.1) > 0.33)
			node->SetTile(CreateTile(tilesets.at(6)));
		else
			node->SetTile(CreateTile(tilesets.at(1)));

	}

	GridTraversal g2{ grid };

	while (g2.HasNext()){
		auto node = g2.Next();
		node->GetTile().CreateTileSprite(CreateSimpleNeighbourMask(node));
	}
}

static unique_ptr<Tile> CreateTile(const Tileset& tileset){
	if (tileset.IsSimple())
		return make_unique<TileSimple>(tileset);
	return make_unique<TileExtended>(tileset);
}
