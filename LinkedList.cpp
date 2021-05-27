
#include "LinkedList.h"

LinkedList::LinkedList()
{
    head = nullptr;
    size = 0;
}
LinkedList::~LinkedList() {}

void LinkedList::removeFront()
{
    if (!isEmpty())
    {
        sharedNodePtr next = head->next;
        head = next;
    }
}

sharedTilePtr LinkedList::getFrontTile()
{
    sharedTilePtr returnTile = nullptr;
    if (!isEmpty())
    {
        returnTile = head->tile;
    }
    return returnTile;
}

void LinkedList::pushBack(sharedTilePtr tile)
{
    sharedNodePtr n = std::make_shared<Node>(tile, nullptr);
    if (isEmpty())
    {
        head = n;
    }
    else
    {
        sharedNodePtr current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = n;
    }
    size++;
}

bool LinkedList::isEmpty()
{
    return getSize() == 0;
}

sharedNodePtr LinkedList::getHead()
{
    return head;
}

int LinkedList::getSize()
{
    return size;
}

bool LinkedList::removeNode(sharedTilePtr tile)
{
    bool canRemove = false;

    if (head != nullptr)
    {
        sharedNodePtr deleteNode = head;
        sharedNodePtr prevNode = nullptr;

        // repeat while node is not nullptr
        while (deleteNode != nullptr && !canRemove)
        {
            // if tile matches then remove node
            if (deleteNode->tile->compareTile(tile))
            {
                if (prevNode == nullptr)
                    head = deleteNode->next;
                else
                    prevNode->next = deleteNode->next;

                // delete deleteNode;
                deleteNode = nullptr;
                canRemove = true;
            }
            else
            {
                prevNode = deleteNode;
                deleteNode = deleteNode->next;
            }
        }
    }

    return canRemove;
}

bool LinkedList::tileExists(sharedTilePtr tile)
{
    bool tileExists = false;

    if (head != nullptr)
    {
        sharedNodePtr currNode = head;

        // repeat while node is not nullptr
        while (currNode != nullptr && !tileExists)
        {
            // if tile matches
            if (currNode->tile->compareTile(tile))
                tileExists = true;
            else
                currNode = currNode->next;
        }
    }
    return tileExists;
}

std::string LinkedList::listToString()
{
    sharedNodePtr currNode = head;
    std::string result = "";

    while (currNode != nullptr)
    {
        result = result + currNode->tile->getColour() + std::to_string(currNode->tile->getShape());

        if (currNode->next != nullptr)
            result = result + ",";

        currNode = currNode->next;
    }

    return result;
}
