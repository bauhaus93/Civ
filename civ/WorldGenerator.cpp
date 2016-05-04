#include "WorldGenerator.h"

using namespace std;

WorldGenerator::WorldGenerator(){
}


WorldGenerator::~WorldGenerator(){
}

void WorldGenerator::Generate(Grid & grid, std::vector<Tileset>& tilesets){
	GridTraversal g{ grid };

	while (g.HasNext()){
		auto node = g.Next();
		node->SetTile(make_unique<Tile>(tilesets.at(common::Random(tilesets.size()))));
	}

	g = GridTraversal(grid);

	while (g.HasNext()){
		auto node = g.Next();
		node->GetTile().InitializeSprite(0);
	}
}
