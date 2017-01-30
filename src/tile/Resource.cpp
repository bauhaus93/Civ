#include "Resource.h"

using namespace std;


Resource::Resource(const Sprite& sprite_):
	sprite{ sprite_ }{
}

Resource::Resource(const Resource& other):
	sprite{ other.sprite }{
}

const Sprite& Resource::GetSprite() const{
	return sprite;
}
