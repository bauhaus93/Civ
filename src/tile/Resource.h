#pragma once

#include <memory>

#include "engine/Sprite.h"

class Resource{

	std::shared_ptr<const Sprite> sprite;
public:
	explicit Resource(std::shared_ptr<Sprite> sprite_);
	Resource(const Resource& other);

	~Resource() = default;
	std::shared_ptr<const Sprite> GetSprite() const;
};
