#include "Resource.h"

using namespace std;


Resource::Resource(shared_ptr<Sprite> sprite_):
	sprite{ sprite_ }{
}

Resource::Resource(const Resource& other):
	sprite{ other.sprite }{
}
