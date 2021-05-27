#ifndef GAME_H
#define GAME_H

#include <vector>
#include <regex>

#include "LinkedList.h"
#include "Tile.h"
#include "Player.h"
#include "TileBag.h"

using std::string;
using std::vector;
using std::shared_ptr;

#define FIX_COL '@'
#define FIX_SHAPE '0'

#define PLACE_MIN_STR_INDEX 12
#define PLACE_TILE_INDEX 6

#define REPLACE_TILE_INDEX 8

#define TILE_STRING_LENGTH 2

#define FILE_STRING_INDEX 5

#define ROW_COUNT 26
#define COLUMN_COUNT 26

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

typedef std::shared_ptr<Player> sharedPlayerPtr;
typedef std::shared_ptr<Tile> sharedTilePtr;
typedef std::shared_ptr<LinkedList> sharedLinkedListPtr;
typedef std::shared_ptr<TileBag> sharedTileBagPtr;

class Game
{
    public:
        Game();
        Game(std::ifstream &inputfile);
        ~Game();

        void readBoard(std::ifstream &inputfile);
        void readBag(std::ifstream &inputfile);

        void startGame();

        void playTurn(sharedPlayerPtr player);

        sharedPlayerPtr addPlayer(int playerID);
        sharedPlayerPtr addPlayer(int playerID, std::ifstream& inputfile);

        void printBoard();

        void printTurnInfo(sharedPlayerPtr currentPlayer);
        bool replaceTile(sharedPlayerPtr player, sharedTilePtr tile);
        bool placeTile(sharedPlayerPtr player, sharedTilePtr tile, int row, int col);

        void saveGame(string fileName, sharedPlayerPtr player);

        bool tileValidation(sharedTilePtr tile, int row, int col, int &score);

        bool inputAction(sharedPlayerPtr player);

    private:
        // 2D Vector
        vector<vector<sharedTilePtr> > boardEnv;
        sharedTileBagPtr tileBag;
        sharedPlayerPtr player1;
        sharedPlayerPtr player2;
        sharedPlayerPtr player3;
        sharedPlayerPtr player4;
        bool boardHasTile;
};

#endif // GAME_H