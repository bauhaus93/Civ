#pragma once

#include <memory>

#include "Node.h"
#include "Tileset.h"

class Grid{

	std::shared_ptr<Node> root;
	std::shared_ptr<Node> view;

	std::shared_ptr<Node> CreateLinkedTwoRow(int size);

	class IterateAll{

		std::shared_ptr<Node> operator++();

		std::shared_ptr<Node> curr;
		std::shared_ptr<Node> lastRowRoot;
		
	};

public:
	Grid();
	~Grid();

	void Create(int sizeX, int sizeY);
	void Fill(Tileset & ts);
	void Render(int screenX, int screenY);
	
};

