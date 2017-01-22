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


Node::~Node(){

}

void Node::RenderRow(int screenX, int screenY, int maxX){
	Node* curr = this;

	while (screenX < maxX && curr != nullptr){
		curr->Render(screenX, screenY);
		screenX += 64;
		curr = curr->GetEast();
	}
}

uint8_t CreateNeighbourMask(Node* node){
	uint8_t mask = 0;
	auto& onTileset = node->GetTile().GetTerrainset();

	if (SAME_NEIGHBOUR(node, onTileset, GetNortheast))
		mask |= (uint8_t)Neighbour::NE;

	if (SAME_NEIGHBOUR(node, onTileset, GetSoutheast))
		mask |= (uint8_t)Neighbour::SE;

	if (SAME_NEIGHBOUR(node, onTileset, GetSouthwest))
		mask |= (uint8_t)Neighbour::SW;

	if (SAME_NEIGHBOUR(node, onTileset, GetNorthwest))
		mask |= (uint8_t)Neighbour::NW;


	if (SAME_NEIGHBOUR(node, onTileset, GetNorth))
		mask |= (uint8_t)Neighbour::N;

	if (SAME_NEIGHBOUR(node, onTileset, GetEast))
		mask |= (uint8_t)Neighbour::E;

	if (SAME_NEIGHBOUR(node, onTileset, GetSouth))
		mask |= (uint8_t)Neighbour::S;

	if (SAME_NEIGHBOUR(node, onTileset, GetWest))
		mask |= (uint8_t)Neighbour::W;

	return mask;
}
