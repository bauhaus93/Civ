#include "WorldGenerator.h"

/* This makes good landmass/ocean noise for now:
noise.GetOctavedNoise(node->GetX(), node->GetY(), 6, 0.2, 0.02) > 0.33 || noise.GetOctavedNoise(node->GetX(), node->GetY(), 3, 0.5, 0.1) > 0.33)
*/

using namespace std;

WorldGenerator::WorldGenerator(const TileFactory& tileFactory_, uint32_t seed):
	tileFactory{ tileFactory_ },
	rng{ seed },
	landmassNoise{ static_cast<uint32_t>(rng()) },
	temperatureNoise{ static_cast<uint32_t>(rng()) },
	moistureNoise{ static_cast<uint32_t>(rng()) },
	elevationNoise{ static_cast<uint32_t>(rng()) }{
}

void WorldGenerator::Generate(Grid& grid){
	auto start = common::Time();
	Logger::Write("Generating world");

	GridTraversal g{ grid };

	while (g.HasNext()){
		CalculateNode(*g.Next());
	}
	Logger::Write("First Traversal in " + to_string(common::TimeDiff(start)) + "ms");

	GridTraversal g2{ grid };

	while (g2.HasNext()){
		auto node = g2.Next();
		auto& tile = node->GetTile();
		tile.UpdateTerrainNeighbourMask(CreateNeighbourMask(node));
		tile.CreateSprite();
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

	elevation *= 1;
	temperature *= 1;
	moisture *= 1;

	if(!isLand){
		node.SetTile(tileFactory.CreateTile("ocean"));
		return;
	}

	if(IsMountain(elevation, temperature, moisture))
		node.SetTile(tileFactory.CreateTile("mountains"));
	else if(IsHills(elevation, temperature, moisture))
		node.SetTile(tileFactory.CreateTile("hills"));
	else if(IsDesert(elevation, temperature, moisture))
		node.SetTile(tileFactory.CreateTile("desert"));
	else if(IsPrairie(elevation, temperature, moisture))
		node.SetTile(tileFactory.CreateTile("prairie"));
	else if(IsJungle(elevation, temperature, moisture))
		node.SetTile(tileFactory.CreateTile("jungle"));
	else if(IsSwamp(elevation, temperature, moisture))
		node.SetTile(tileFactory.CreateTile("swamp"));
	else if(IsForest(elevation, temperature, moisture))
		node.SetTile(tileFactory.CreateTile("forest"));
	else if(IsArctic(elevation, temperature, moisture))
		node.SetTile(tileFactory.CreateTile("arctic"));
	else if(IsTundra(elevation, temperature, moisture))
		node.SetTile(tileFactory.CreateTile("tundra"));
	else
		node.SetTile(tileFactory.CreateTile("grasslands"));

}

bool WorldGenerator::IsMountain(double elevation, double temperature, double moisture){
	if(elevation > 0.8 && elevation > 0.5 * temperature && elevation > 0.5 * moisture)
		return true;
	return false;
}

bool WorldGenerator::IsHills(double elevation, double temperature, double moisture){
	if(elevation > 0.7 && elevation > 0.75 * moisture)
		return true;
	return false;
}

bool WorldGenerator::IsDesert(double elevation, double temperature, double moisture){
	if(temperature > 0.75 && moisture < 0.4)
		return true;
	return false;
}

bool WorldGenerator::IsPrairie(double elevation, double temperature, double moisture){
	if(temperature > 0.4 && moisture < 0.33)
		return true;
	return false;
}

bool WorldGenerator::IsJungle(double elevation, double temperature, double moisture){
	if(temperature > 0.75 && moisture > 0.5)
		return true;
	return false;
}

bool WorldGenerator::IsSwamp(double elevation, double temperature, double moisture){
	if(temperature > 0.3 && temperature < 0.6 && moisture > 0.7 && elevation < 0.4)
		return true;
	return false;
}

bool WorldGenerator::IsForest(double elevation, double temperature, double moisture){
	if(temperature > 0.25 && temperature < 0.5 && moisture > 0.4 && elevation > 0.4)
		return true;
	return false;
}

bool WorldGenerator::IsArctic(double elevation, double temperature, double moisture){
	if(temperature < 0.15)
		return true;
	return false;
}

bool WorldGenerator::IsTundra(double elevation, double temperature, double moisture){
	if(temperature < 0.20 && moisture > 0.25)
		return true;
	return false;
}
