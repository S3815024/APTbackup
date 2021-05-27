#include <algorithm>
#include <random>

#include "TileBag.h"
#include "TileCodes.h"

TileBag::TileBag()
{
    list = std::make_shared<LinkedList>();
    
    generateTiles();
    shuffleTiles();
    createList();
}

TileBag::~TileBag() {}

TileBag::TileBag(std::vector<sharedTilePtr> &bag) : list(std::make_shared<LinkedList>())
{
    tiles = bag;
    createList();
}

void TileBag::generateTiles()
{
    Colour colours[MAX_TILES] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
    Shape shapes[MAX_TILES] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};
    for (Colour colour : colours)
    {
        for (Shape shape : shapes)
        {
            sharedTilePtr tile = std::make_shared<Tile>(colour, shape);
            tiles.push_back(tile);
            tiles.push_back(tile);
        }
    }
}

sharedLinkedListPtr TileBag::getList()
{
    return list;
}

void TileBag::createList()
{
    for(sharedTilePtr tile : tiles)
    {
        sharedTilePtr _tile = std::make_shared<Tile>(tile->getColour(), tile->getShape());
        list->pushBack(_tile);
    }
}

void TileBag::shuffleTiles()
{
    std::random_device randDevice;
    std::default_random_engine randEngine(randDevice());
    std::shuffle(std::begin(tiles), std::end(tiles), randEngine);
}