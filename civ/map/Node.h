#pragma once

#include <memory>

#include "Tile/Tile.h"

#define GET_NEIGHBOUR(a, b) {if(a() != nullptr) return a()->b();\
							else if(b() != nullptr) return b()->a();\
							return nullptr;}

#define SAME_NEIGHBOUR(node, tileset, neighbour) ( node->neighbour() != nullptr && tileset == node->neighbour()->GetTile().GetTileset() )



class Node{

	std::unique_ptr<Tile> tile;
	int		x;
	int		y;

	Node*  northeast;
	Node*  northwest;
	Node*  southeast;
	Node*  southwest;


public:
					Node(int x_, int y_);
					~Node();
					
	inline void		SetTile(std::unique_ptr<Tile> tile_);
	inline Tile&	GetTile(void){ return *tile; }
	inline void		Render(int x, int y);
	void			RenderRow(int startX, int startY, int maxX);
	int				GetX(void) const{ return x; };
	int				GetY(void) const{ return y; }
	bool			IsOdd(void) const{ return GetY() % 2 == 1; }

	inline void		LinkWithNortheast(Node* ne);
	inline void		LinkWithNorthwest(Node* nw);
	inline void		LinkWithSoutheast(Node* se);
	inline void		LinkWithSouthwest(Node* sw);

	inline void		SetNortheast(Node* ne);
	inline void		SetNorthwest(Node* nw);
	inline void		SetSoutheast(Node* se);
	inline void		SetSouthwest(Node* sw);

	inline Node*	GetNortheast(void);
	inline Node*	GetNorthwest(void);
	inline Node*	GetSoutheast(void);
	inline Node*	GetSouthwest(void);

	inline Node*	GetNorth(void);
	inline Node*	GetSouth(void);
	inline Node*	GetWest(void);
	inline Node*	GetEast(void);

};

uint8_t CreateSimpleNeighbourMask(Node* node);

void Node::SetTile(std::unique_ptr<Tile> tile_){
	tile = move(tile_);
}

inline void Node::Render(int screenX, int screenY){
	tile->Render(screenX, screenY);
}

void Node::LinkWithNortheast(Node* ne){
	SetNortheast(ne);
	ne->SetSouthwest(this);
}

void Node::LinkWithNorthwest(Node* nw){
	SetNorthwest(nw);
	nw->SetSoutheast(this);
}

void Node::LinkWithSoutheast(Node* se){
	SetSoutheast(se);
	se->SetNorthwest(this);
}

void Node::LinkWithSouthwest(Node* sw){
	SetSouthwest(sw);
	sw->SetNortheast(this);
}

void Node::SetNortheast(Node* ne){
	northeast = ne;
}

void Node::SetNorthwest(Node* nw){
	northwest = nw;

}

void Node::SetSoutheast(Node* se){
	southeast = se;

}

void Node::SetSouthwest(Node* sw){
	southwest = sw;
}

Node* Node::GetNortheast(void){
	return northeast;
}

Node* Node::GetNorthwest(void){
	return northwest;
 }

Node* Node::GetSoutheast(void){
	return southeast;
}

Node* Node::GetSouthwest(void){
	return southwest;
}

Node* Node::GetNorth(void){
	GET_NEIGHBOUR(GetNorthwest, GetNortheast);
}

Node* Node::GetSouth(void){
	GET_NEIGHBOUR(GetSouthwest, GetSoutheast);
}

Node* Node::GetWest(void){
	GET_NEIGHBOUR(GetNorthwest, GetSouthwest);
}

Node* Node::GetEast(void){
	GET_NEIGHBOUR(GetNortheast, GetSoutheast);
}



