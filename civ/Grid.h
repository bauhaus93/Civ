#pragma once

#include <vector>
#include <memory>

#include "Node.h"
#include "Tileset.h"

class Grid{

	friend class GridTraversal;


private:
	Node* root;
	Node* view;
	
public:
	
	Grid();
	~Grid();

	void Create(int sizeX, int sizeY);
	void Render(const Rect& field);

	Node* CreateBlock(int sizeX, int sizeY);
	Node* LinkRows(std::vector<Node*>& top, std::vector<Node*>& bot);
	void LinkBlock(Node* root, Node* newBlock);

	void AlignViewPos(int x, int y);
	
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



