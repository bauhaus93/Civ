#include "Grid.h"

using namespace std;

Grid::Grid(){

}


Grid::~Grid(){
	vector<Node*> nodes;
	GridTraversal g{ *this };

	while (g.HasNext()){
		nodes.push_back(g.Next());
	}

	while (!nodes.empty()){
		delete nodes.back();
		nodes.pop_back();
	}
}

void Grid::Create(int sizeX, int sizeY){

	root = CreateBlock(sizeX, sizeY);
	view = root;
}

void Grid::Render(int screenX, int screenY){

	int drawX = 0;
	int drawY = 0;
	bool advanced = false;

	GridTraversalRow g{ *this };

	while (drawY < screenY){
		if (advanced)
			drawX = 32;
		else
			drawX = 0;

		while (drawX < screenX && g.HasNext()){
			auto node = g.Next();
			node->Render(drawX, drawY);
			drawX += 64;
		}
		advanced = !advanced;
		if (!g.HasNextRow())
			break;
		g.NextRow();
		drawY += 16;
	}
}


Node* Grid::CreateBlock(int sizeX, int sizeY){
	Node* myRoot = nullptr;
	Node* curr = nullptr;
	auto rowTop = make_unique<vector<Node*>>();
	auto rowBot = make_unique<vector<Node*>>();

	cout << "create block" << endl;
	for (int x = 0; x < sizeX; x++){
		rowTop->push_back(new Node(x, 0));
	}
	curr = rowTop->front();
	myRoot = curr;

	for (int y = 1; y < sizeY; y++){
		for (int x = 0; x < sizeX; x++){
			rowBot->push_back(new Node(x, y));
		}
		curr = LinkRows(*rowTop, *rowBot);
		rowTop = move(rowBot);
		rowBot = make_unique<vector<Node*>>();
	}
	return myRoot;
}

Node* Grid::LinkRows(vector<Node*>& top, vector<Node*>& bot){
	decltype(top.size()) n = 0;
	bool advanced = (top[0]->GetY() % 2) != 0;

	while (n < top.size()){
		if (advanced){
			top[n]->LinkWithSouthwest(bot[n]);
			if (n + 1 < bot.size())
				top[n]->LinkWithSoutheast(bot[n+1]);

		}
		else{
			top[n]->LinkWithSoutheast(bot[n]);
			if (n >= 1)
				top[n]->LinkWithSouthwest(bot[n-1]);
		}
		n++;
	}
	return bot.front();
}


GridTraversal::GridTraversal(Grid& grid) :
	curr{ grid.root },
	rowFirst{ grid.root }{

	if (curr->GetSouthwest() != nullptr)
		advanced = true;
	else
		advanced = false;
}

GridTraversal::~GridTraversal(){

}

Node* GridTraversal::Next(void){
	auto currReturn = curr;

	curr = curr->GetEast();
	if (curr == nullptr){
		if (advanced)
			curr = rowFirst->GetSouthwest();
		else
			curr = rowFirst->GetSoutheast();
		rowFirst = curr;
		advanced = !advanced;
	}
	return currReturn;
}

GridTraversalRow::GridTraversalRow(Grid & grid) :
	GridTraversal{ grid }{
}

GridTraversalRow::~GridTraversalRow(void){
}

Node * GridTraversalRow::Next(void){
	auto currReturn = curr;
	curr = curr->GetEast();

	return currReturn;
}

void GridTraversalRow::NextRow(void){
	if (advanced)
		curr = rowFirst->GetSouthwest();
	else
		curr = rowFirst->GetSoutheast();
	rowFirst = curr;
	advanced = !advanced;
}
