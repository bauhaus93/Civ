#include "Node.h"
#include "Grid.h"



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
	auto& onTileset = node->GetTile().GetTileset();

	if (SAME_NEIGHBOUR(node, onTileset, GetNortheast))
		mask |= 1;

	if (SAME_NEIGHBOUR(node, onTileset, GetSoutheast))
		mask |= 2;

	if (SAME_NEIGHBOUR(node, onTileset, GetSouthwest))
		mask |= 4;

	if (SAME_NEIGHBOUR(node, onTileset, GetNorthwest))
		mask |= 8;


	if (SAME_NEIGHBOUR(node, onTileset, GetNorth))
		mask |= 16;

	if (SAME_NEIGHBOUR(node, onTileset, GetEast))
		mask |= 32;

	if (SAME_NEIGHBOUR(node, onTileset, GetSouth))
		mask |= 64;

	if (SAME_NEIGHBOUR(node, onTileset, GetWest))
		mask |= 128;
		
	return mask;
}
