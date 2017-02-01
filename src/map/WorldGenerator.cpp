#include "WorldGenerator.h"

/* This makes good landmass/ocean noise for now:
noise.GetOctavedNoise(node->GetX(), node->GetY(), 6, 0.2, 0.02) > 0.33 || noise.GetOctavedNoise(node->GetX(), node->GetY(), 3, 0.5, 0.1) > 0.33)
*/

using namespace std;

WorldGenerator::WorldGenerator(const TileFactory& tileFactory_, uint32_t seed):
	tileFactory{ tileFactory_ },
	rng{ seed },
	landmassNoise{ static_cast<uint32_t>(rng()) },
	elevationNoise{ static_cast<uint32_t>(rng()) },
	temperatureNoise{ static_cast<uint32_t>(rng()) },
	moistureNoise{ static_cast<uint32_t>(rng()) },
	elevationMod{ 1.0 },
	temperatureMod{ 1.0 },
	moistureMod{ 1.0 }{
	Logger::Write("Landmass generation seed: " + to_string(seed));
}

void WorldGenerator::Generate(Grid& grid){
	Generate(grid, 1.0, 1.0, 1.0);
}

void WorldGenerator::Generate(Grid& grid, double elevationMod_, double temperatureMod_, double moistureMod_){
	auto start = common::Time();
	Logger::Write("Generating world");

	elevationMod = elevationMod_;
	temperatureMod = temperatureMod_;
	moistureMod = moistureMod_;


	GridTraversal g{ grid };

	while (g.HasNext()){
		CalculateNode(*g.Next());
	}
	Logger::Write("First Traversal in " + to_string(common::TimeDiff(start)) + "ms");

	GridTraversal g2{ grid };

	while (g2.HasNext()){
		auto node = g2.Next();
		node->UpdateTile();
	}
	Logger::Write("World generated in " + to_string(common::TimeDiff(start)) + "ms");
}

void WorldGenerator::CalculateNode(Node& node){
	int x = node.GetX();
	int y = node.GetY();

	bool isLand = landmassNoise.GetOctavedNoise(x, y, 6, 0.2, 0.02) > 0.33 || landmassNoise.GetOctavedNoise(x, y, 3, 0.5, 0.1) > 0.2;
	//normalizing to [0.0, 1.0] bc easier to divide/multiply a value
	double elevation = (1 + elevationNoise.GetOctavedNoise(x, y, 4, 4.0, 0.02)) / 2;
	double temperature = (1 + temperatureNoise.GetOctavedNoise(x, y, 4, 2.0, 0.01)) / 2;
	double moisture = (1 + moistureNoise.GetOctavedNoise(x, y, 4, 2.0, 0.01)) / 2;

	elevation *= elevationMod;
	temperature *= temperatureMod;
	moisture *= moistureMod;

	unique_ptr<Tile> tile = nullptr;
	if(!isLand)
		tile = tileFactory.CreateTile("ocean");
	else if(IsMountain(elevation, temperature, moisture))
		tile = tileFactory.CreateTile("mountains");
	else if(IsHills(elevation, temperature, moisture))
		tile = tileFactory.CreateTile("hills");
	else if(IsDesert(elevation, temperature, moisture))
		tile = tileFactory.CreateTile("desert");
	else if(IsPrairie(elevation, temperature, moisture))
		tile = tileFactory.CreateTile("prairie");
	else if(IsJungle(elevation, temperature, moisture))
		tile = tileFactory.CreateTile("jungle");
	else if(IsSwamp(elevation, temperature, moisture))
		tile = tileFactory.CreateTile("swamp");
	else if(IsForest(elevation, temperature, moisture))
		tile = tileFactory.CreateTile("forest");
	else if(IsArctic(elevation, temperature, moisture))
		tile = tileFactory.CreateTile("arctic");
	else if(IsTundra(elevation, temperature, moisture))
		tile = tileFactory.CreateTile("tundra");
	else
		tile = tileFactory.CreateTile("grasslands");

	tile->RandomizeBaseSprite(rng);
	tile->RandomizeResource(rng);

	node.SetTile(move(tile));

}
