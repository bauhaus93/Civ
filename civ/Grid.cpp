#include "Grid.h"

using namespace std;

Grid::Grid(unique_ptr<Sprite> mouseClickComparator_) :
	mouseClickComparator{ move(mouseClickComparator_) }{

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
	center = root;// ->GetSoutheast();

}

void Grid::Render(const Rect& field){

	int drawX = 0;
	int drawY = 0;
	int startX = field.x;
	int startY = field.y;
	bool advanced = view->GetY() % 2 != 0;

	if (view->GetY() % 2 != 0){
		startX += 32;
		startY -= 16;
	}
	
	GridTraversalRow g{ *this };

	drawY = startY;
	while (drawY < field.h){
		if (advanced)
			drawX = startX + 32;
		else
			drawX = startX;

		while (drawX < field.w && g.HasNext()){
			auto node = g.Next();

			/*if (drawY == 0){
				if (node->GetNorthwest() != nullptr)
					node->GetNorthwest()->Render(drawX - 32, drawY - 16);
			}

			if (drawX <= 32){
				if (node->GetNorthwest() != nullptr)
					node->GetNorthwest()->Render(drawX - 32, drawY - 16);
			}*/

			static int blink = 10;
			if (node != center)
				node->Render(drawX, drawY);
			else if (blink-- < 0){
				node->Render(drawX, drawY);
				if (blink == -10)
					blink = 10;
			}

			/*if (drawY == 0){
				if (node->GetNortheast() != nullptr)
					node->GetNortheast()->Render(drawX + 32, drawY - 16);

			}*/

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

void Grid::CenterToScreen(int screenX, int screenY, const Rect& boundaries){

	RGBAColor col = mouseClickComparator->PixelAt(screenX % 64, screenY % 32);

	int relX = screenX / 64;
	int relY = 2 * (screenY / 32);

	switch (col.r){
		case 107:
			relX--;
			relY--;
			break;
		case 159:
			relY--;
			break;
		case 71:
			relY++;
			break;
		case 167:
			relX--;
			relY++;
		case 27:
			break;
		default:
			cout << "DEFAULT SHOULD NOT HAPPEN LEL: " << (int)col.r << ", " << (int)col.g << ", " << (int)col.b << ", " << (int)col.a << endl;
			break;
	}

	int diffX = relX - center->GetX() + view->GetX();
	int diffY = relY - center->GetY() + view->GetY();
	cout << "x = " << relX << ", y = " << relY << ", diff: " << diffX << ", " << diffY << endl;
	center = GoRelative(center, diffX, diffY);
	AlignView(center, Rect{ 0, 0, 1024, 768 });

	cout << "center @ " << center->GetX() << ", " << center->GetY() << endl;
	cout << "view @ " << view->GetX() << ", " << view->GetY() << endl;
}

Node* Grid::GoRelative(Node* node, int x, int y){

	static Sprite s{ Sprite(Rect{ 0, 0, 64, 32 }) };

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

void Grid::AlignView(Node* node, const Rect& field){
	int x = field.w / 2;
	int y = field.h / 2;

	while (y > 0){
		if (node->GetNorth() != nullptr)
			node = node->GetNorth();
		y -= 32;
	}

	while (x > 0){
		if (node->GetWest() != nullptr)
			node = node->GetWest();
		else
			break;
		x -= 64;
	}
	view = node;
}

void Grid::AlignViewToCenter(const Rect& field){
	AlignView(center, field);
}

Node* Grid::GetCenterNode(const Rect& field){
	int x = 0;
	int y = 0;
	int centerX = field.w / 2;
	int centerY = field.h / 2;
	auto node = view;

	//static Sprite s{ Sprite(Rect{ 0, 0, 64, 32 }) };


	while (x + 64 < centerX && y + 32 < centerY){
		node = node->GetSoutheast()->GetSoutheast();
		/*auto dummy = make_unique<Tile>(0, s);
		dummy->InitializeSprite();
		node->SetTile(move(dummy));*/
		x += 64;
		y += 32;
	}

	while (x + 64 < centerX){
		node = node->GetEast();
		/*auto dummy = make_unique<Tile>(0, s);
		dummy->InitializeSprite();
		node->SetTile(move(dummy));*/
		x += 64;
	}

	while (y + 32 < centerY){
		node = node->GetSouth();
		/*auto dummy = make_unique<Tile>(0, s);
		dummy->InitializeSprite();
		node->SetTile(move(dummy));*/
		y += 32;
	}

	x = centerX - x;
	y = centerY - y;
	//cout << x << ", " << y << endl;

	if (x == 64 && y == 32)
		node = node->GetSoutheast();

	/*auto dummy = make_unique<Tile>(0, s);
	dummy->InitializeSprite();
	node->SetTile(move(dummy));*/

	return node;
}




GridTraversal::GridTraversal(Grid& grid) :
	curr{ grid.view },
	rowFirst{ grid.view }{

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
