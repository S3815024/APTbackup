
#include "Node.h"

//Deep copy
Node::Node(sharedTilePtr tile, sharedNodePtr next)
{
  this->tile = std::make_shared<Tile>(tile->getColour(), tile->getShape());
  this->next = next;
}

Node::~Node()
{
  
}

Node::Node(Node &other)
{
  this->tile = std::make_shared<Tile>(*(other.tile));
  this->next = other.next;
}
