#include "Resource.h"

using namespace std;


Resource::Resource(Sprite&& sprite_) noexcept:
	sprite{ move(sprite_) }{
}

Resource::Resource(Resource&& other) noexcept{
	sprite = move(other.sprite);
}


const Sprite& Resource::GetSprite() const{
	return sprite;
}

Resource& Resource::operator=(Resource&& other) noexcept{
	sprite = move(other.sprite);
	return *this;
}
