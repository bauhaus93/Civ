#include "Node.h"

Node::Node(int x_, int y_) :
	tile{ nullptr },
	x{ x_ },
	y{ y_ },
	northeast{ nullptr },
	northwest{ nullptr },
	southeast{ nullptr },
	southwest{ nullptr }{
}

void Node::RenderRow(int screenX, int screenY, int maxX){
	Node* curr = this;

	while (screenX < maxX && curr != nullptr){
		curr->Render(screenX, screenY);
		screenX += 64;
		curr = curr->GetEast();
	}
}

void Node::UpdateTile(){
	tile->UpdateSprite(GetNeighbourMask());
}

uint8_t Node::GetNeighbourMask(){
	uint8_t mask = 0;
	auto& onTileset = tile->GetTerrainset();

	if (SAME_NEIGHBOUR(this, onTileset, GetNortheast))
		mask |= (uint8_t)Neighbour::NE;

	if (SAME_NEIGHBOUR(this, onTileset, GetSoutheast))
		mask |= (uint8_t)Neighbour::SE;

	if (SAME_NEIGHBOUR(this, onTileset, GetSouthwest))
		mask |= (uint8_t)Neighbour::SW;

	if (SAME_NEIGHBOUR(this, onTileset, GetNorthwest))
		mask |= (uint8_t)Neighbour::NW;


	if (SAME_NEIGHBOUR(this, onTileset, GetNorth))
		mask |= (uint8_t)Neighbour::N;

	if (SAME_NEIGHBOUR(this, onTileset, GetEast))
		mask |= (uint8_t)Neighbour::E;

	if (SAME_NEIGHBOUR(this, onTileset, GetSouth))
		mask |= (uint8_t)Neighbour::S;

	if (SAME_NEIGHBOUR(this, onTileset, GetWest))
		mask |= (uint8_t)Neighbour::W;
	return mask;
}

void Node::UpdateDither(){

}
