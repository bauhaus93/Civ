#include "Grid.h"


using namespace std;


Grid::Grid():
	mouseClickComparator{}{

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

void Grid::SetMouseClickComparator(Sprite mouseClickComparator_){
	mouseClickComparator = move(mouseClickComparator_);
}

void Grid::Create(int sizeX, int sizeY){

	root = CreateBlock(sizeX, sizeY);
	center = root;
	view = root;
}

void Grid::Render(const Rect& field){

	Node* curr = view;
	int drawX = field.x;
	int drawY = field.y;
	bool fullFirst = false;

	if (advanceAll)
		drawX += 64;

	//special case row over view node
	if (curr->GetNortheast() != nullptr)
		curr->GetNortheast()->RenderRow(drawX + 32, drawY - 16, field.w);

	while (drawY < field.h){

		//special case node left to first, with avoidance of overwriting first node of  preceding row
		if (!fullFirst && curr->GetNorthwest() != nullptr)
			curr->GetNorthwest()->Render(drawX - 32, drawY - 16);

		curr->RenderRow(drawX, drawY, field.w);

		if (curr == view){
			Engine::Instance().SetColor(RGBAColor{ 0xFF, 0, 0, 0xFF });
			Engine::Instance().DrawFillRect(Rect{ drawX + 32 - 5, drawY + 16 - 5, 10, 10 });
		}

		if (fullFirst){
			curr = curr->GetSouthwest();
			drawX -= 32;
		}
		else{
			curr = curr->GetSoutheast();
			drawX += 32;
		}

		if (curr == nullptr)
			break;

		fullFirst = !fullFirst;
		drawY += 16;
	}

	//special case Node in bottom left corner (take NW of the first row out of bounds, equals to W of first node in last drawn row, but without repetitive checks in loop
	if (curr != nullptr && curr->GetNorthwest() != nullptr)
		curr->GetNorthwest()->Render(drawX - 32, drawY - 16);

	Engine::Instance().SetColor(RGBAColor{ 0xFF, 0, 0, 0xFF });
	for (int y = field.y; y < field.h; y += 32)
		Engine::Instance().DrawLine(field.x, y, field.w, y);
	for (int x = field.y; x < field.w; x += 64)
		Engine::Instance().DrawLine(x, field.y, x, field.h);

	Engine::Instance().DrawLine(field.x, field.y, field.w, field.h);
	Engine::Instance().DrawLine(field.x, field.h, field.w, field.y);

}

Node* Grid::CreateBlock(int sizeX, int sizeY){
	Node* myRoot = nullptr;
	Node* curr = nullptr;
	auto rowTop = make_unique<vector<Node*>>();
	auto rowBot = make_unique<vector<Node*>>();

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
				top[n]->LinkWithSoutheast(bot[n + 1]);

		}
		else{
			top[n]->LinkWithSoutheast(bot[n]);
			if (n >= 1)
				top[n]->LinkWithSouthwest(bot[n - 1]);
		}
		n++;
	}
	return bot.front();
}

void Grid::CenterToClick(int screenX, int screenY, int maxX, int maxY){

	if (advanceAll)
		screenX -= 64;

	center = NodeAtScreenPos(screenX, screenY);
	AlignViewToCenter(maxX, maxY);
}

Node* Grid::GoRelative(Node* node, int x, int y){


	while (x > 0){
		if (node->GetEast() != nullptr)
			node = node->GetEast();
		else
			break;
		x--;
	}

	while (x < 0){
		if (node->GetWest() != nullptr)
			node = node->GetWest();
		else
			break;
		x++;
	}

	bool advanced = node->GetY() % 2 != 0;
	while (y > 0){
		if (advanced){
			if (node->GetSouthwest() != nullptr)
				node = node->GetSouthwest();
			else
				break;
		}
		else{
			if (node->GetSoutheast() != nullptr)
				node = node->GetSoutheast();
			else
				break;
		}
		advanced = !advanced;
		y--;
	}

	while (y < 0){
		if (advanced){
			if (node->GetNorthwest() != nullptr)
				node = node->GetNorthwest();
			else
				break;
		}
		else{
			if (node->GetNortheast() != nullptr)
				node = node->GetNortheast();
			else
				break;
		}
		advanced = !advanced;
		y++;
	}
	return node;
}

Node* Grid::NodeAtScreenPos(int x, int y){
	auto node = view;

	while (x >= 64){

		if (node->GetEast() != nullptr)
			node = node->GetEast();
		else
			break;
		x -= 64;
	}

	while (y >= 32){

		if (node->GetSouth() != nullptr)
			node = node->GetSouth();
		else
			break;
		y -= 32;
	}

	if (x >= 0 && y>= 0 && x < 64 && y < 32){
		RGBAColor col = mouseClickComparator.PixelAt(x, y);

		switch (col.r){
			case 107:
				if (node->GetNorthwest() != nullptr)
					node = node->GetNorthwest();
				break;
			case 159:
				if (node->GetNortheast() != nullptr)
					node = node->GetNortheast();
				break;
			case 71:
				if (node->GetSoutheast() != nullptr)
					node = node->GetSoutheast();
				break;
			case 167:
				if (node->GetSouthwest() != nullptr)
					node = node->GetSouthwest();
			case 27:
				break;
			default:
				throw CivException("switch(mouseClickComparator->PixelAt)", "Unknown case");
		}
	}
	//cout << "node is @ " << node->GetX() << ", " << node->GetY() << endl;

	return node;
}

void Grid::AlignView(Node* node, int screenSizeX, int screenSizeY){
	int x = screenSizeX / 2;
	int y = screenSizeY / 2;

	while (x >= 64){

		if (node->GetWest() != nullptr)
			node = node->GetWest();
		else
			break;
		x -= 64;
	}

	while (y >= 32){

		if (node->GetNorth() != nullptr)
			node = node->GetNorth();
		else
			break;
		y -= 32;
	}

	//if view is on top boundary try to get the NW node as view
	if (node->GetNorth() == nullptr){
		if (node->GetNorthwest() != nullptr)
			node = node->GetNorthwest();
	}
	else if (node->GetWest() != nullptr){		//if view is not on any boundary, get SE node as view
		node = node->GetSoutheast();
	}

	if (node->IsOdd() && node->GetWest() == nullptr){
		advanceAll = true;
	}
	else
		advanceAll = false;

	//cout << "left: " << x << ", " << y << endl;
	view = node;
}

void Grid::AlignViewToCenter(int screenSizeX, int screenSizeY){
	AlignView(center, screenSizeX, screenSizeY);
}

GridTraversal::GridTraversal(Grid& grid) :
	curr{ grid.root },
	rowFirst{ grid.root }{

	if (curr->IsOdd())
		advanced = true;
	else
		advanced = false;
}

GridTraversal::~GridTraversal(){

}

Node* GridTraversal::Next(){
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
