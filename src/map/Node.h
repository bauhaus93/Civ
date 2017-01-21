#pragma once

#include <memory>

#include "tile/Tile.h"

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
	inline Tile&	GetTile(){ return *tile; }
	inline void		Render(int x, int y);
	void			RenderRow(int startX, int startY, int maxX);
	int				GetX() const{ return x; };
	int				GetY() const{ return y; }
	bool			IsOdd() const{ return GetY() % 2 == 1; }

	inline void		LinkWithNortheast(Node* ne);
	inline void		LinkWithNorthwest(Node* nw);
	inline void		LinkWithSoutheast(Node* se);
	inline void		LinkWithSouthwest(Node* sw);

	inline void		SetNortheast(Node* ne);
	inline void		SetNorthwest(Node* nw);
	inline void		SetSoutheast(Node* se);
	inline void		SetSouthwest(Node* sw);

	inline Node*	GetNortheast();
	inline Node*	GetNorthwest();
	inline Node*	GetSoutheast();
	inline Node*	GetSouthwest();

	inline Node*	GetNorth();
	inline Node*	GetSouth();
	inline Node*	GetWest();
	inline Node*	GetEast();

};

uint8_t CreateNeighbourMask(Node* node);

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

Node* Node::GetNortheast(){
	return northeast;
}

Node* Node::GetNorthwest(){
	return northwest;
 }

Node* Node::GetSoutheast(){
	return southeast;
}

Node* Node::GetSouthwest(){
	return southwest;
}

Node* Node::GetNorth(){
	GET_NEIGHBOUR(GetNorthwest, GetNortheast);
}

Node* Node::GetSouth(){
	GET_NEIGHBOUR(GetSouthwest, GetSoutheast);
}

Node* Node::GetWest(){
	GET_NEIGHBOUR(GetNorthwest, GetSouthwest);
}

Node* Node::GetEast(){
	GET_NEIGHBOUR(GetNortheast, GetSoutheast);
}
