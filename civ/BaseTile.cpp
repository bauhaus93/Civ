#include "BaseTile.h"

using namespace std;

BaseTile::BaseTile(Sprite& floor_):
	floor{ floor_ } {


}

void BaseTile::Render(int x, int y){
	floor.Render(x, y);
}

