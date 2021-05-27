#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include <memory>
#include "TileCodes.h"

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile
{
  public:
    Tile(Colour c, Shape s);
    Tile(Tile& tile);
    ~Tile();

    Colour getColour();

    Shape getShape();

    bool compareTile(std::shared_ptr<Tile> tile);

  private:
    Colour colour;
    Shape shape;
};

typedef std::shared_ptr<Tile> sharedTilePtr;

#endif // ASSIGN2_TILE_H
