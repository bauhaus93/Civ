#include "Tileset.h"

using namespace std;

Tileset::Tileset(const string& name_, unsigned int resourceChance_) :
	name{ name_ },
	resourceChance{ resourceChance_ }{
}

Tileset::Tileset(Tileset&& other) noexcept{
	cout << "Tileset move c'tor start" << endl;
	name = other.name;
	resourceChance = other.resourceChance;
	floor = move(other.floor);
	resource = move(other.resource);
	cout << "Tileset move c'tor end" << endl;
}

void Tileset::AddFloor(Sprite&& sprite){
	floor.push_back(move(sprite));
}

void Tileset::AddResource(Resource&& res){
	resource.push_back(move(res));
}

const Sprite& Tileset::GetRandomFloor(void) const{
	return floor.at(common::Random(floor.size()));
}

const Resource& Tileset::GetResource(int id) const{
	return resource.at(id);
}

int Tileset::GetRandomResource(void) const{
	return common::Random() < resourceChance ? common::Random(resource.size()) : -1;
}