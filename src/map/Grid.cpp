#include "Grid.h"

using namespace std;


Grid::Grid():
    root{ nullptr },
    view{ nullptr },
    center{ nullptr },
    advanceAll{ false },
    mouseClickComparator{ SpriteManager::Instance().CreateFromSpritesheet(TERRAIN1, Rect{ 66, 447, 64, 32}) }{

}

Grid::~Grid(){
    vector<Tile*> tiles;
    GridTraversal g{ *this };

    while (g.HasNext()){
        tiles.push_back(g.Next());
    }

    while (!tiles.empty()){
        delete tiles.back();
        tiles.pop_back();
    }
}

void Grid::Create(int sizeX, int sizeY){

    root = CreateBlock(sizeX, sizeY);
    center = root;
    view = root;
}

void Grid::Render(const Rect& field){

    Tile* curr = view;
    int drawX = field.x;
    int drawY = field.y;
    bool fullFirst = false;

    if (advanceAll)
        drawX += 64;

    //special case row over view tile
    if (curr->GetNeighbour(Neighbour::NE) != nullptr)
        curr->GetNeighbour(Neighbour::NE)->RenderRow(drawX + 32, drawY - 16, field.w);

    while (drawY < field.h){

        //special case tile left to first, with avoidance of overwriting first tile of  preceding row
        if (!fullFirst && curr->GetNeighbour(Neighbour::NW) != nullptr)
            curr->GetNeighbour(Neighbour::NW)->Render(drawX - 32, drawY - 16);

        curr->RenderRow(drawX, drawY, field.w);

        /*Helping square
        if (curr == view){
            Engine::Instance().SetColor(RGBAColor{ 0xFF, 0, 0, 0xFF });
            Engine::Instance().DrawFillRect(Rect{ drawX + 32 - 5, drawY + 16 - 5, 10, 10 });
        }*/

        if (fullFirst){
            curr = curr->GetNeighbour(Neighbour::SW);
            drawX -= 32;
        }
        else{
            curr = curr->GetNeighbour(Neighbour::SE);
            drawX += 32;
        }

        if (curr == nullptr)
            break;

        fullFirst = !fullFirst;
        drawY += 16;
    }

    //special case Node in bottom left corner (take NW of the first row out of bounds, equals to W of first tile in last drawn row, but without repetitive checks in loop
    if (curr != nullptr && curr->GetNeighbour(Neighbour::NW) != nullptr)
        curr->GetNeighbour(Neighbour::NW)->Render(drawX - 32, drawY - 16);

    /* Helping lines
    Engine::Instance().SetColor(RGBAColor{ 0xFF, 0, 0, 0xFF });
    for (int y = field.y; y < field.h; y += 32)
        Engine::Instance().DrawLine(field.x, y, field.w, y);
    for (int x = field.y; x < field.w; x += 64)
        Engine::Instance().DrawLine(x, field.y, x, field.h);

    Engine::Instance().DrawLine(field.x, field.y, field.w, field.h);
    Engine::Instance().DrawLine(field.x, field.h, field.w, field.y);*/

}

Tile* Grid::CreateBlock(int sizeX, int sizeY){
    Tile* myRoot = nullptr;
    Tile* curr = nullptr;
    auto rowTop = make_unique<vector<Tile*>>();
    auto rowBot = make_unique<vector<Tile*>>();

    for (int x = 0; x < sizeX; x++){
        rowTop->push_back(new Tile(x, 0));
    }
    curr = rowTop->front();
    myRoot = curr;

    for (int y = 1; y < sizeY; y++){
        for (int x = 0; x < sizeX; x++){
            rowBot->push_back(new Tile(x, y));
        }
        curr = LinkRows(*rowTop, *rowBot);
        rowTop = move(rowBot);
        rowBot = make_unique<vector<Tile*>>();
    }
    return myRoot;
}

Tile* Grid::LinkRows(vector<Tile*>& top, vector<Tile*>& bot){
    decltype(top.size()) n = 0;
    bool advanced = (top[0]->GetY() % 2) != 0;

    while (n < top.size()){
        if (advanced){
            top[n]->LinkNeighbours(bot[n], Neighbour::SW);
            if (n + 1 < bot.size())
                top[n]->LinkNeighbours(bot[n + 1], Neighbour::SE);

        }
        else{
            top[n]->LinkNeighbours(bot[n], Neighbour::SE);
            if (n >= 1)
                top[n]->LinkNeighbours(bot[n - 1], Neighbour::SW);
        }
        n++;
    }
    return bot.front();
}

void Grid::CenterToClick(int screenX, int screenY, int maxX, int maxY){

    if (advanceAll)
        screenX -= 64;

    center = TileAtScreenPos(screenX, screenY);
    AlignViewToCenter(maxX, maxY);
}

/*Tile* Grid::GoRelative(Tile* tile, int x, int y){


    while (x > 0){
        if (tile->GetEast() != nullptr)
            tile = tile->GetEast();
        else
            break;
        x--;
    }

    while (x < 0){
        if (tile->GetWest() != nullptr)
            tile = tile->GetWest();
        else
            break;
        x++;
    }

    bool advanced = Tile->GetY() % 2 != 0;
    while (y > 0){
        if (advanced){
            if (tile->GetSouthwest() != nullptr)
                tile = tile->GetSouthwest();
            else
                break;
        }
        else{
            if (tile->GetSoutheast() != nullptr)
                tile = tile->GetSoutheast();
            else
                break;
        }
        advanced = !advanced;
        y--;
    }

    while (y < 0){
        if (advanced){
            if (tile->GetNorthwest() != nullptr)
                tile = tile->GetNorthwest();
            else
                break;
        }
        else{
            if (tile->GetNortheast() != nullptr)
                tile = tile->GetNortheast();
            else
                break;
        }
        advanced = !advanced;
        y++;
    }
    return tile;
}*/

Tile* Grid::TileAtScreenPos(int x, int y){
    auto tile = view;

    while (x >= 64){

        if (tile->GetNeighbour(Neighbour::E) != nullptr)
            tile = tile->GetNeighbour(Neighbour::E);
        else
            break;
        x -= 64;
    }

    while (y >= 32){

        if (tile->GetNeighbour(Neighbour::S) != nullptr)
            tile = tile->GetNeighbour(Neighbour::S);
        else
            break;
        y -= 32;
    }

    if (x >= 0 && y>= 0 && x < 64 && y < 32){
        RGBAColor col = mouseClickComparator->PixelAt(x, y);

        switch (col.r){
            case 107:
                if (tile->GetNeighbour(Neighbour::NW) != nullptr)
                    tile = tile->GetNeighbour(Neighbour::NW);
                break;
            case 159:
                if (tile->GetNeighbour(Neighbour::NE) != nullptr)
                    tile = tile->GetNeighbour(Neighbour::NE);
                break;
            case 71:
                if (tile->GetNeighbour(Neighbour::SE) != nullptr)
                    tile = tile->GetNeighbour(Neighbour::SE);
                break;
            case 167:
                if (tile->GetNeighbour(Neighbour::SW) != nullptr)
                    tile = tile->GetNeighbour(Neighbour::SW);
            case 27:
                break;
            default:
                throw CivException("Grid::TileAtScreenPos", "switch(mouseClickComparator): Unknown case");
        }
    }
    //cout << "tile is @ " << tile->GetX() << ", " << tile->GetY() << endl;

    return tile;
}

void Grid::AlignView(Tile* tile, int screenSizeX, int screenSizeY){
    int x = screenSizeX / 2;
    int y = screenSizeY / 2;

    while (x >= 64){

        if (tile->GetNeighbour(Neighbour::W) != nullptr)
            tile = tile->GetNeighbour(Neighbour::W);
        else
            break;
        x -= 64;
    }

    while (y >= 32){

        if (tile->GetNeighbour(Neighbour::N) != nullptr)
            tile = tile->GetNeighbour(Neighbour::N);
        else
            break;
        y -= 32;
    }

    //if view is on top boundary try to get the NW tile as view
    if (tile->GetNeighbour(Neighbour::N) == nullptr){
        if (tile->GetNeighbour(Neighbour::NW) != nullptr)
            tile = tile->GetNeighbour(Neighbour::NW);
    }
    else if (tile->GetNeighbour(Neighbour::W) != nullptr){        //if view is not on any boundary, get SE tile as view
        tile = tile->GetNeighbour(Neighbour::SE);
    }

    if (tile->IsOdd() && tile->GetNeighbour(Neighbour::W) == nullptr){
        advanceAll = true;
    }
    else
        advanceAll = false;

    //cout << "left: " << x << ", " << y << endl;
    view = tile;
}

void Grid::AlignViewToCenter(int screenSizeX, int screenSizeY){
    AlignView(center, screenSizeX, screenSizeY);
}

GridTraversal::GridTraversal(Grid& grid) :
    root{ grid.root },
    curr{ grid.root },
    rowFirst{ grid.root }{

    if(curr == nullptr)
        throw CivException("GridTraversal::GridTraversal", "Root of grid is nullptr!");

    if (curr->IsOdd())
        advanced = true;
    else
        advanced = false;
}

Tile* GridTraversal::Next(){
    auto currReturn = curr;

    curr = curr->GetNeighbour(Neighbour::E);

    if (curr == nullptr){
        if (advanced)
            curr = rowFirst->GetNeighbour(Neighbour::SW);
        else
            curr = rowFirst->GetNeighbour(Neighbour::SE);
        rowFirst = curr;
        advanced = !advanced;
    }
    return currReturn;
}

void GridTraversal::Reset(){
    curr = root;
    rowFirst = root;

    if(curr == nullptr)
       throw CivException("GridTraversal::GridTraversal", "Root is nullptr!");

    if (curr->IsOdd())
        advanced = true;
    else
        advanced = false;
}
