
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include <iostream>
#include "Node.h"

class LinkedList
{
public:
   LinkedList();
   ~LinkedList();

   void pushBack(sharedTilePtr tile);
   bool isEmpty();
   void removeFront();
   sharedTilePtr getFrontTile();
   sharedNodePtr getHead();
   int getSize();
   
   /**
    * Remove a node containing the tile
    * 
    * @param tile Tile to check within the node
    * @return Returns `true` if node can be removed else returns `false`
    */
   bool removeNode(sharedTilePtr tile);

   /**
    * Check if tile exists
    * 
    * @param tile Tile to check
    * @return Returns `true` if tile exists else returns `false`
    */
   bool tileExists(sharedTilePtr tile);

   std::string listToString();

private:
	int size;
   sharedNodePtr head;
};

typedef std::shared_ptr<LinkedList> sharedLinkedListPtr;

#endif // ASSIGN2_LINKEDLIST_H
