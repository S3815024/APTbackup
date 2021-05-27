#include <vector>
#include "Tile.h"
#include "LinkedList.h"

#define MAX_TILES 6

class TileBag
{
    public:
        TileBag();
        TileBag(std::vector<sharedTilePtr> &bag);
        ~TileBag();
        void shuffleTiles();
        sharedLinkedListPtr getList();

    private:
        std::vector<sharedTilePtr> tiles; // all the tiles "in the box"
        sharedLinkedListPtr list;

        void generateTiles();
        void createList();
};

