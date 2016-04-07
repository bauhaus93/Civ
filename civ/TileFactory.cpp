#include "TileFactory.h"

using namespace std;

TileFactory::TileFactory(){
}

void TileFactory::AddTileset(unique_ptr<Tileset> tileset){
	tilesets.insert(make_pair(tileset->GetName(), move(tileset)));
}


