#pragma once

#include <vector>
#include <memory>

#include "tile/Tile.h"
#include "engine/Sprite.h"
#include "engine/SpriteManager.h"

class Grid{

	friend class GridTraversal;

private:
	Tile* root;
	Tile* view;
	Tile* center;
	bool advanceAll;

	std::shared_ptr<Sprite> mouseClickComparator;

	Tile* CreateBlock(int sizeX, int sizeY);
	Tile* LinkRows(std::vector<Tile*>& top, std::vector<Tile*>& bot);
	//Node* GoRelative(Node* node, int x, int y);

public:

	Grid();
	~Grid();

	void Create(int sizeX, int sizeY);
	void Render(const Rect& field);

	void CenterToClick(int screenX, int screenY, int maxX, int maxY);

	Node* NodeAtScreenPos(int x, int y);

	void AlignView(Node* node, int screenSizeX, int screenSizeY);
	void AlignViewToCenter(int screenSizeX, int screenSizeY);

};

class GridTraversal{

protected:
	Node*	curr;
	Node*	rowFirst;
	bool	advanced;

public:
	explicit GridTraversal(Grid& grid);
	virtual ~GridTraversal();
	virtual Node* Next();
	bool HasNext() const{ return curr != nullptr; }
};
