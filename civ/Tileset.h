#pragma once

#include <vector>
#include <string>
#include <memory>


#include "Sprite.h"
#include "Resource.h"


enum class NeighbourInfo{
	DIFFERENT = 0,
	SAME = 1
};

enum class NeighbourDiamond{
	TOP_RIGHT = 1,
	BOT_RIGHT = 2,
	BOT_LEFT = 4,
	TOP_LEFT = 8,

	TOP = 16,
	RIGHT = 32,
	BOT = 64,
	LEFT = 128
};


class Tileset{

private:
	std::string		name;
	unsigned int	resourceChance;

	std::vector<Sprite>		floor;
	std::vector<Resource>	resource;

public:
	Tileset(const std::string& name_, unsigned int resourceChance_);
	Tileset(Tileset&& other) noexcept;

	~Tileset(void) = default;

	void AddFloor(Sprite&& sprite);
	void AddResource(Resource&& res);

	const Sprite& GetRandomFloor(void) const;
	const Resource& GetResource(int id) const;
	int GetRandomResource(void) const ;
};
