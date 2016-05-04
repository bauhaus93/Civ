#include "Resource.h"



Resource::Resource(Sprite& sprite_):
	sprite{ sprite_ }{
}


Resource::~Resource(){
}

Sprite& Resource::GetSprite(void) const{
	return sprite;
}
