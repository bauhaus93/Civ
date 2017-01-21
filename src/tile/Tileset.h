#pragma once

#include <vector>
#include <string>
#include <memory>

#include "engine/Sprite.h"
#include "Resource.h"
#include "common/Common.h"

class Tileset{

private:
	std::string		name;
	unsigned int	resourceChance;
	bool			simple;


	std::vector<Sprite>		floor;
	std::vector<Resource>	resource;

public:
	Tileset(const std::string& name_, unsigned int resourceChance_, bool simple_);
	Tileset(Tileset&& other) noexcept;
	~Tileset() = default;

	bool IsSimple() const{ return simple; }

	void AddFloor(Sprite&& sprite);
	void AddResource(Resource&& res);

	const Sprite& GetRandomFloor() const;
	const Resource& GetResource(int id) const;
	int GetRandomResource() const ;

	bool operator==(const Tileset& other) const { return this == &other; };
	bool operator!=(const Tileset& other) const { return this != &other; };
};
