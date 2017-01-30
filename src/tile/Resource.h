#pragma once

#include <memory>

#include "engine/Sprite.h"

class Resource{

	const Sprite& sprite;
public:
	explicit Resource(const Sprite& sprite_);
	Resource(const Resource& other);

	~Resource() = default;
	const Sprite& GetSprite() const;
};
