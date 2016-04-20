#pragma once

#include <vector>
#include <memory>

#include "Node.h"
#include "Sprite.h"
#include "Renderer.h"

class Grid{

	friend class GridTraversal;


private:
	Node* root;
	Node* view;
	Node* center;
	bool advanceAll;

	std::unique_ptr<Sprite> mouseClickComparator;


public:
	
	Grid(std::unique_ptr<Sprite> mouseClickComparator_);
	~Grid();

	void Create(int sizeX, int sizeY);
	void Render(const Rect& field);

	Node* CreateBlock(int sizeX, int sizeY);
	Node* LinkRows(std::vector<Node*>& top, std::vector<Node*>& bot);

	void CenterToScreen(int screenX, int screenY, const Rect& boundaries);

	Node* GoRelative(Node* node, int x, int y);

	void AlignView(Node* node, const Rect & field);

	void AlignViewToCenter(const Rect & field);

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