#include "Resource.h"

using namespace std;


Resource::Resource(Sprite&& sprite_) noexcept:
	sprite{ sprite_ }{
}

Resource::Resource(Resource&& other) noexcept{
	sprite = move(other.sprite);
}

Resource::Resource(const Resource& other):
	sprite{ other.sprite }{

}


Resource::~Resource(){
}

const Sprite& Resource::GetSprite(void) const{
	return sprite;
}

Resource& Resource::operator=(Resource&& other) noexcept{
	sprite = move(other.sprite);
	return *this;
}
