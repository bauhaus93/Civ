#include "WorldGenerator.h"

using namespace std;

static unique_ptr<Tile> CreateTile(const Tileset& tileset);

WorldGenerator::WorldGenerator(){
}


WorldGenerator::~WorldGenerator(){
}

void WorldGenerator::Generate(Grid & grid, std::vector<Tileset>& tilesets){
	GridTraversal g{ grid };

	while (g.HasNext()){
		auto node = g.Next();
		node->SetTile(CreateTile(tilesets.at(common::Random(tilesets.size()))));
		
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