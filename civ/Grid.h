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

	std::unique_ptr<Sprite> mouseClickComparator;


public:
	
	Grid(std::unique_ptr<Sprite> mouseClickComparator_);
	~Grid();

	void Create(int sizeX, int sizeY);
	void Render(const Rect& field);

	Node* CreateBlock(int sizeX, int sizeY);
	Node* LinkRows(std::vector<Node*>& top, std::vector<Node*>& bot);
	void LinkBlock(Node* root, Node* newBlock);

	void CenterToScreen(int screenX, int screenY, const Rect& boundaries);

	Node* GoRelative(Node* node, int x, int y);

	void AlignView(Node* node, const Rect & field);

	void AlignViewToCenter(const Rect & field);

	Node* GetCenterNode(const Rect& field);
	
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

class GridTraversalRow: public GridTraversal{

public:
	GridTraversalRow(Grid& grid);
	virtual ~GridTraversalRow(void);
	virtual Node* Next(void) override;
	void NextRow(void);
	bool HasNextRow(void){ return rowFirst != nullptr; }
};



