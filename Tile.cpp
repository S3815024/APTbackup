#include "Tile.h"

Tile::Tile(Colour c, Shape s)
{
  this->colour = c;
  this->shape = s;
}

Tile::Tile(Tile& tile)
{
  colour = tile.colour;
  shape = tile.shape;
}

Tile::~Tile() {}

Colour Tile::getColour()
{
  return colour;
}

Shape Tile::getShape()
{
  return shape;
}

bool Tile::compareTile(sharedTilePtr tile)
{
  bool result = false;

  if (colour == tile->getColour() && shape == tile->getShape())
    result = true;
  
  return result;
}