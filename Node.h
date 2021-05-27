
#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"

class Node {
public:

   Node(sharedTilePtr tile, std::shared_ptr<Node> next);
   Node(Node& other);
   
   ~Node();

   sharedTilePtr    tile;
   std::shared_ptr<Node>    next;
};

typedef std::shared_ptr<Node> sharedNodePtr;

#endif // ASSIGN2_NODE_H
