#pragma once

#include <vector>
#include <memory>

#include "Node.h"
#include "Sprite.h"

class Grid{

	friend class GridTraversal;

private:
	Node* root;
	Node* view;
	Node* center;
	bool advanceAll;

	Sprite mouseClickComparator;

	Node* CreateBlock(int sizeX, int sizeY);
	Node* LinkRows(std::vector<Node*>& top, std::vector<Node*>& bot);
	Node* GoRelative(Node* node, int x, int y);

public:
	
	Grid();
	~Grid();

	void SetMouseClickComparator(Sprite mouseClickComparator_);

	void Create(int sizeX, int sizeY);
	void Render(const Rect& field);

	void CenterToClick(int screenX, int screenY, int maxX, int maxY);

	Node * NodeAtScreenPos(int x, int y);

	void AlignView(Node* node, int screenSizeX, int screenSizeY);
	void AlignViewToCenter(int screenSizeX, int screenSizeY);

};

class GridTraversal{

protected:
	Node*	curr;
	Node*	rowFirst;
	bool	advanced;

public:
	GridTraversal(Grid& grid);
	virtual ~GridTraversal(void);
	virtual Node* Next(void);
	bool HasNext(void) const{ return curr != nullptr; }
};