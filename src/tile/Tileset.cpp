#include "Tileset.h"

using namespace std;

Tileset::Tileset(const string& name_, unsigned int resourceChance_, bool simple_) :
	name{ name_ },
	resourceChance{ resourceChance_ },
	simple{ simple_ }{
}

Tileset::Tileset(Tileset&& other) noexcept{
	name = other.name;
	resourceChance = other.resourceChance;
	floor = move(other.floor);
	resource = move(other.resource);
}

void Tileset::AddFloor(Sprite&& sprite){
	floor.push_back(move(sprite));
}

void Tileset::AddResource(Resource&& res){
	resource.push_back(move(res));
}

const Sprite& Tileset::GetRandomFloor() const{
	return floor.at(common::Random(floor.size()));
}

const Resource& Tileset::GetResource(int id) const{
	return resource.at(id);
}

int Tileset::GetRandomResource() const{
	return common::Random() < resourceChance ? common::Random(resource.size()) : -1;
}
