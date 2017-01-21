#include "Tileset.h"

using namespace std;

Tileset::Tileset(const string& name_, unsigned int resourceChance_, bool simple_) :
	name{ name_ },
	resourceChance{ resourceChance_ },
	simple{ simple_ }{
}

Tileset::Tileset(Tileset&& other) noexcept:
	name{ other.name},
	resourceChance{ other.resourceChance },
	simple{ other.simple},
	floor{ move(other.floor) },
	resource{ move(other.resource) },
	extension{ move(other.extension)}{

}

void Tileset::AddFloor(Sprite&& sprite){
	floor.push_back(move(sprite));
}

void Tileset::AddResource(Resource&& res){
	resource.push_back(move(res));
}

void Tileset::AddExtension(Sprite&& sprite, uint8_t neighbourMask){
	extension.emplace(neighbourMask, sprite);
}

const Sprite& Tileset::GetRandomFloor() const{
	return floor.at(common::Random(floor.size()));
}

const Resource& Tileset::GetResource(int id) const{
	return resource.at(id);
}
const Sprite& Tileset::GetExtension(uint8_t neighbourMask) const{
	auto iter = extension.find(neighbourMask);
	if(iter == extension.end())
		throw CivException("Tileset::GetExtension", "Neighourmask " + to_string((int)neighbourMask) + " not in tileset \"" + name + "\"");
	return iter->second;
}

int Tileset::GetRandomResource() const{
	return common::Random() < resourceChance ? common::Random(resource.size()) : -1;
}
