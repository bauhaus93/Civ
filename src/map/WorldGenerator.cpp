#include "WorldGenerator.h"

/* This makes good landmass/ocean noise for now:
noise.GetOctavedNoise(node->GetX(), node->GetY(), 6, 0.2, 0.02) > 0.33 || noise.GetOctavedNoise(node->GetX(), node->GetY(), 3, 0.5, 0.1) > 0.33)
*/

using namespace std;

WorldGenerator::WorldGenerator(){
}


WorldGenerator::~WorldGenerator(){
}

void WorldGenerator::Generate(Grid& grid, const TileFactory& tileFactory){
	auto start = common::Time();
	Logger::Write("Generating world");

	SimplexNoise noise{};
	GridTraversal g{ grid };

	while (g.HasNext()){
		auto node = g.Next();

		if(noise.GetOctavedNoise(node->GetX(), node->GetY(), 6, 0.2, 0.02) > 0.33 || noise.GetOctavedNoise(node->GetX(), node->GetY(), 3, 0.5, 0.1) > 0.33)
			node->SetTile(tileFactory.CreateTile("jungle"));
		else
			node->SetTile(tileFactory.CreateTile("grasslands"));

	}
	Logger::Write("First Traversal in " + to_string(common::TimeDiff(start)) + "ms");

	GridTraversal g2{ grid };

	while (g2.HasNext()){
		auto node = g2.Next();
		node->GetTile().CreateTileSprite(CreateNeighbourMask(node));
	}
	Logger::Write("World generated in " + to_string(common::TimeDiff(start)) + "ms");
}
