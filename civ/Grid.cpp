#include "Grid.h"

using namespace std;

Grid::Grid(){

}


Grid::~Grid(){
}

void Grid::Create(int sizeX, int sizeY){

	root = CreateLinkedTwoRow(sizeX);
	view = root;

	/*for (auto y = 0; y < sizeY; y++){
		for (auto x = 0; x < sizeX; x++){

		}
	}*/
}

void Grid::Fill(Tileset& ts){



}

void Grid::Render(int screenX, int screenY){

	int drawX = 0;
	int drawY = 0;
	bool odd = false;

	auto lastRowRoot = root;
	auto node = root;

	while (drawY < screenY){
		if (odd)
			drawX = 32;
		else
			drawX = 0;

		while (drawX < screenX){
			node->Render(drawX, drawY);
			node = node->GetEast();
			drawX += 64;

			if (node == nullptr)
				break;
		}

		if (odd)
			node = lastRowRoot->GetSouthwest();
		else
			node = lastRowRoot->GetSoutheast();

		odd = !odd;

		if (node == nullptr)
			break;
	}
}

shared_ptr<Node> Grid::CreateLinkedTwoRow(int size){
	auto root = make_shared<Node>();
	auto lastNode = root;

	for (int i = 0; i < 2 * size - 1; i++){
		auto newNode = make_shared<Node>();

		if (i % 2 == 0)
			lastNode->LinkWithSoutheast(newNode);
		else
			lastNode->LinkWithNortheast(newNode);
		lastNode = newNode;
	}
	return root;
}
