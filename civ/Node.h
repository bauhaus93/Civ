#pragma once

#include <memory>

#include "Tile.h"

#define GET_NEIGHBOUR(a, b) {if(a() != nullptr) return a()->b();\
							else if(b() != nullptr) return b()->a();\
							return nullptr;}

class Node{

	std::unique_ptr<Tile> tile;

	std::shared_ptr<Node>  northeast;
	std::shared_ptr<Node>  northwest;
	std::shared_ptr<Node>  southeast;
	std::shared_ptr<Node>  southwest;


public:
					Node();
					~Node();
	inline void		SetTile(std::unique_ptr<Tile> tile_);
	inline void		Render(int x, int y);

	inline void		LinkWithNortheast(std::shared_ptr<Node> ne);
	inline void		LinkWithNorthwest(std::shared_ptr<Node> nw);
	inline void		LinkWithSoutheast(std::shared_ptr<Node> se);
	inline void		LinkWithSouthwest(std::shared_ptr<Node> sw);

	inline void		SetNortheast(std::shared_ptr<Node> ne);
	inline void		SetNorthwest(std::shared_ptr<Node> nw);
	inline void		SetSoutheast(std::shared_ptr<Node> se);
	inline void		SetSouthwest(std::shared_ptr<Node> sw);

	inline std::shared_ptr<Node>	GetNortheast(void);
	inline std::shared_ptr<Node>	GetNorthwest(void);
	inline std::shared_ptr<Node>	GetSoutheast(void);
	inline std::shared_ptr<Node>	GetSouthwest(void);

	inline std::shared_ptr<Node>	GetNorth(void);
	inline std::shared_ptr<Node>	GetSouth(void);
	inline std::shared_ptr<Node>	GetWest(void);
	inline std::shared_ptr<Node>	GetEast(void);

};

void Node::SetTile(std::unique_ptr<Tile> tile_){
	tile = move(tile_);
}

inline void Node::Render(int x, int y){
	tile->Render(x, y);
}

void Node::LinkWithNortheast(std::shared_ptr<Node> ne){
	SetNortheast(ne);
	ne->SetSouthwest(static_cast<std::shared_ptr<Node>>(this));
}

void Node::LinkWithNorthwest(std::shared_ptr<Node> nw){
	SetNorthwest(nw);
	nw->SetSoutheast(static_cast<std::shared_ptr<Node>>(this));
}

void Node::LinkWithSoutheast(std::shared_ptr<Node> se){
	SetSoutheast(se);
	se->SetNorthwest(static_cast<std::shared_ptr<Node>>(this));
}

void Node::LinkWithSouthwest(std::shared_ptr<Node> sw){
	SetSouthwest(sw);
	sw->SetNortheast(static_cast<std::shared_ptr<Node>>(this));
}

void Node::SetNortheast(std::shared_ptr<Node> ne){
	northeast = ne;
}

void Node::SetNorthwest(std::shared_ptr<Node> nw){
	northwest = nw;

}

void Node::SetSoutheast(std::shared_ptr<Node> se){
	southeast = se;

}

void Node::SetSouthwest(std::shared_ptr<Node> sw){
	southwest = sw;
}

std::shared_ptr<Node> Node::GetNortheast(void){
	return northeast;
}

std::shared_ptr<Node> Node::GetNorthwest(void){
	return northwest;
 }

std::shared_ptr<Node> Node::GetSoutheast(void){
	return southeast;
}

std::shared_ptr<Node> Node::GetSouthwest(void){
	return southwest;
}

std::shared_ptr<Node> Node::GetNorth(void){
	GET_NEIGHBOUR(GetNorthwest, GetNortheast);
}

std::shared_ptr<Node> Node::GetSouth(void){
	GET_NEIGHBOUR(GetSouthwest, GetSoutheast);
}

std::shared_ptr<Node> Node::GetWest(void){
	GET_NEIGHBOUR(GetNorthwest, GetSouthwest);
}

std::shared_ptr<Node> Node::GetEast(void){
	GET_NEIGHBOUR(GetNortheast, GetSoutheast);
}



