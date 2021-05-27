#include <fstream>
#include <regex>

#include "Game.h"
#include "Util.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

using std::regex_match;
using std::regex;

#define ID_PLAYER_ONE 1
#define ID_PLAYER_TWO 2
#define ID_PLAYER_THREE 3
#define ID_PLAYER_Four 4

Game::Game()
{
    boardEnv = vector<vector<sharedTilePtr> >(ROW_COUNT, vector<sharedTilePtr>(COLUMN_COUNT, nullptr));
    tileBag = std::make_shared<TileBag>();
    player1 = nullptr;
    player2 = nullptr;
    player3 = nullptr;
    player4 = nullptr;
    boardHasTile = false;
}

Game::Game(std::ifstream& inputfile)
{
    player1 = addPlayer(ID_PLAYER_ONE, inputfile);
    player2 = addPlayer(ID_PLAYER_TWO, inputfile);
    player3 = addPlayer(ID_PLAYER_THREE, inputfile);
    player4 = addPlayer(ID_PLAYER_Four, inputfile);
    tileBag = std::make_shared<TileBag>();
    boardEnv = vector<vector<sharedTilePtr>>(ROW_COUNT, vector<sharedTilePtr>(COLUMN_COUNT, nullptr));
    boardHasTile = false;

	readBoard(inputfile);
	vector<Tile> bag;
	readBag(inputfile);
	std::string current;
	std::getline(inputfile, current);
	inputfile.close();
	if (player1->getPlayerName() == current)
	{
		playTurn(player1);
	}
    if (player2->getPlayerName() == current)
	{
		playTurn(player2);
	}
    if (player3->getPlayerName() == current)
	{
		playTurn(player3);
	}
	else
	{
		playTurn(player4);
	}
}

Game::~Game() {}

void Game::readBoard(std::ifstream& inputfile)
{
	std::string line;
	std::getline(inputfile, line); // discarding the size
	std::getline(inputfile, line);
	while (line != "")
	{
        // get tile string
		std::string tileString = line.substr(0, line.find('@'));

        // get tile
        Colour colour = tileString.front();
        Shape shape = tileString.back()-FIX_SHAPE;
		sharedTilePtr addTileToBoard = std::make_shared<Tile>(colour, shape);

        // get coord string
		line = line.substr(line.find('@') + 1);

        // get coordinates
		std::string coordString = line.substr(0, line.find(','));
        int col = coordString.front()-FIX_COL-1;
        int row = stoi(coordString.substr(1,coordString.length()))-1;

        // add tile to board
		boardEnv[col][row] = addTileToBoard;
		line = line.substr(line.find(' ') + 1);

        // If false set true
        if (!boardHasTile)
            boardHasTile = true;
	}
}

void Game::readBag(std::ifstream& inputfile)
{
	std::string line;
	std::getline(inputfile, line);
	while (line != "")
	{
        // get tile string
		std::string tileString = line.substr(0, line.find(','));

        // get tile
        Colour colour = tileString.front();
        Shape shape = tileString.back()-FIX_SHAPE;
		sharedTilePtr addTileToBag = std::make_shared<Tile>(colour, shape);

        // add tile to tileBag
		tileBag->getList()->pushBack(addTileToBag);
		line = line.substr(line.find(',') + 1);
	}
}

void Game::startGame()
{
    cout << "Starting a New Game" << endl << endl;

    // get player one
    player1 = addPlayer(ID_PLAYER_ONE);

    // get player two
    player2 = addPlayer(ID_PLAYER_TWO);

    // get player three
    player3 = addPlayer(ID_PLAYER_THREE);

    // get player four
    player4 = addPlayer(ID_PLAYER_Four);
    
    cout << "Let's Play" << endl << endl;
    playTurn(player1);
}

void Game::playTurn(sharedPlayerPtr player)
{
    printTurnInfo(player);
    cout << "> ";

    bool validAction = inputAction(player);

    if (!cin.eof())
    {
        // Condition to continue game
        if (tileBag->getList()->getSize() > 0 && player1->getPlayerHand()->getSize() > 0 && player2->getPlayerHand()->getSize() > 0 && player3->getPlayerHand()->getSize() > 0 && player4->getPlayerHand()->getSize() > 0 && validAction)
        {
            if (player->getPlayerID() == 1)
                {playTurn(player2);}
            else if (player->getPlayerID() == 2)
                {playTurn(player3);}
            else if (player->getPlayerID() == 3)
                {playTurn(player4);}
            else{
                playTurn(player1);}
        }
        else
        {
            if (player1->getCurrentScore() > player2->getCurrentScore() && player1->getCurrentScore() > player3->getCurrentScore() && player1->getCurrentScore() > player4->getCurrentScore())
            {
                cout << player1->getPlayerName() << " is the Winner!" << endl;
                cout << "Score: " << player1->getCurrentScore() << endl;
            }
            if (player2->getCurrentScore() > player1->getCurrentScore() && player2->getCurrentScore() > player3->getCurrentScore() && player2->getCurrentScore() > player4->getCurrentScore())
            {
                cout << player2->getPlayerName() << " is the Winner!" << endl;
                cout << "Score: " << player2->getCurrentScore() << endl;
            }
            if (player3->getCurrentScore() > player1->getCurrentScore() && player3->getCurrentScore() > player2->getCurrentScore() && player3->getCurrentScore() > player4->getCurrentScore())
            {
                cout << player3->getPlayerName() << " is the Winner!" << endl;
                cout << "Score: " << player3->getCurrentScore() << endl;
            }
            else
            {
                cout << player4->getPlayerName() << " is the Winner!" << endl;
                cout << "Score: " << player4->getCurrentScore() << endl;
            }
        }
    }
}

sharedPlayerPtr Game::addPlayer(int playerID)
{
    // initialize variable
    string playerName = "";

    // get player name
    cout << "Enter a name for player " << playerID << " (uppercase characters only)" << endl;
    cout << "> ";
    playerName = userInput(ADD_PLAYER);
    cout << endl;

    // create player
    sharedPlayerPtr player = std::make_shared<Player>(playerID, playerName);
    for (int i = 0; i < MAX_TILES; i++)
    {
        player->getPlayerHand()->pushBack(tileBag->getList()->getFrontTile());
        tileBag->getList()->removeFront();
    }

    return player;
}

sharedPlayerPtr Game::addPlayer(int playerID, std::ifstream& inputfile)
{
	string playerName;
	std::getline(inputfile, playerName);
	string line;
	std::getline(inputfile, line);
	int score = std::stoi(line);
	sharedPlayerPtr player = std::make_shared<Player>(playerID, playerName, score);
	std::getline(inputfile, line);
	vector<Tile> tiles;
	while (line != "")
	{
		std::string tileString = line.substr(0, line.find(','));

		Colour colour = tileString.front();
        Shape shape = tileString.back()-FIX_SHAPE;
		sharedTilePtr addTileToHand = std::make_shared<Tile>(colour, shape);

		player->getPlayerHand()->pushBack(addTileToHand);

        // cannot find ","
        if (line.find(',') == std::string::npos)
            line = line.substr(line.find("") + 2);
        else
		    line = line.substr(line.find(',') + 1);
	}

	return player;
}

bool Game::inputAction(sharedPlayerPtr player)
{
    bool validAction = false;
    bool savingGame = false;

    string playerInput = userInput(PLAYER_TURN);

    if (regex_match(playerInput, regex("(place)(.*)")))
    {
        // get tile string
        string tileString = playerInput.substr(PLACE_TILE_INDEX,TILE_STRING_LENGTH);
        Colour colour = tileString.front();
        Shape shape = tileString.back()-FIX_SHAPE;

        sharedTilePtr tileToPlace = std::make_shared<Tile>(colour, shape);

        int subStringCount = playerInput.length()-PLACE_MIN_STR_INDEX;

        // get coord string
        string coordString = playerInput.substr(PLACE_MIN_STR_INDEX,subStringCount);
        int col = coordString.front()-FIX_COL-1;
        int row = stoi(coordString.substr(1,subStringCount))-1;

        validAction = placeTile(player, tileToPlace, row, col);
    }
    else if (regex_match(playerInput, regex("(replace)(.*)")))
    {
        string tileString = playerInput.substr(REPLACE_TILE_INDEX,TILE_STRING_LENGTH);
        Colour colour = tileString.front();
        Shape shape = tileString.back()-FIX_SHAPE;

        sharedTilePtr tileToReplace = std::make_shared<Tile>(colour, shape);

        validAction = replaceTile(player, tileToReplace);
    }

    else if (regex_match(playerInput, regex("(help)(.*)")))
    {
        std::cout << "Press (control+D) at terminal to quit game\n " << std::endl;
        std::cout << "type (place <tile in hand> at <board co-ordinate> to put your selected tile on tileboard)\n " << std::endl;
        std::cout << "type (replace <tile in hand> at <board co-ordinate> to replace your selected tile from hand)\n " << std::endl;
        std::cout << "type (save <name with which you want to save>) to save the game as it is and play later)\n " << std::endl;
    }

    else if (regex_match(playerInput, regex("(save)(.*)")))
    {
        string fileName = playerInput.substr(FILE_STRING_INDEX, playerInput.length()-1);
        saveGame(fileName, player);
        savingGame = true;
    }

    if (!validAction && !cin.eof())
    {
        if (!savingGame)
        {
            //cout << endl << "Invalid Input" << endl;
        }
        cout << "> ";
        validAction = inputAction(player);
    }

    return validAction;

}

void Game::printBoard()
{   
    int number = 0;
    int numLines = 0;
    int digitLength = 0;
    char character = 'A';

    // Print number columns
    cout << "   ";
    for (vector<sharedTilePtr> vec : boardEnv)
    {
        number++;
        digitLength = std::to_string(number).length();
        if (digitLength > 1)
        {
            numLines += digitLength + 1;
            cout << number << " ";
        }
        else
        {
            numLines += digitLength + 2;
            cout << number << "  ";
        }
    }
    cout << endl;

    // Print line break
    cout << "  ";
    for (int i = 0; i <= numLines; i++)
        cout << "-";
    cout << endl;

    // Print board with tiles
    for (vector<sharedTilePtr> vec : boardEnv)
    {
        cout << character << " |";
        for (vector<sharedTilePtr>::iterator it = vec.begin(); it != vec.end(); it++)
        {
            if (*it != nullptr)
            {
                sharedTilePtr tile = *it;
                cout << tile->getColour() << tile->getShape() << "|";
            }
            else
                cout << "  |";
        }
        
        character++;
        cout << endl;
    }
}

void Game::printTurnInfo(sharedPlayerPtr player)
{
    cout << player->getPlayerName() << ", it's your turn" << endl;
    cout << "Score for " << player1->getPlayerName() << ": " << player1->getCurrentScore() << endl;
    cout << "Score for " << player2->getPlayerName() << ": " << player2->getCurrentScore() << endl;
    cout << "Score for " << player3->getPlayerName() << ": " << player3->getCurrentScore() << endl;
    cout << "Score for " << player4->getPlayerName() << ": " << player4->getCurrentScore() << endl << endl;

    printBoard();

    cout << endl << "Your hand is " << endl;
    cout << player->handToString() << endl << endl;
}

bool Game::tileValidation(sharedTilePtr tile, int row, int col, int &score)
{
    bool returnValue = true;

    // check within board bounds
    if (row >= 0 && row < ROW_COUNT && col >= 0 && col < COLUMN_COUNT)
    {
        bool hasTileNeighbour = false;
        bool addPointCheck = false;

        int rowSize = boardEnv.size()-1;
        int colSize = boardEnv.size()-1;

        sharedTilePtr tileOnBoard = nullptr;

        // check if location is empty
        if (boardEnv[col][row] == nullptr && tile != nullptr)
        {
            // Iterate 4 times (Cardinal Direction N S E W)
            for (int i = 0; i < 4 && returnValue; i++)
            {
                int qwirkleCount = 0;
                int tileRow = row;
                int tileCol = col;
                do
                {
                    tileOnBoard = nullptr;

                    // direction and out of bounds check
                    if (i == NORTH && tileRow-1 >= 0)
                    {
                        tileOnBoard = boardEnv[tileCol][tileRow-1];
                        tileRow -= 1;
                    }
                    else if (i == SOUTH && tileRow+1 <= rowSize)
                    {
                        tileOnBoard = boardEnv[tileCol][tileRow+1];
                        tileRow += 1;
                    }
                    else if (i == EAST && tileCol+1 <= colSize)
                    {
                        tileOnBoard = boardEnv[tileCol+1][tileRow];
                        tileCol += 1;
                    }
                    else if (i == WEST && tileCol-1 >= 0)
                    {
                        tileOnBoard = boardEnv[tileCol-1][tileRow];
                        tileCol -= 1;
                    }

                    if (tileOnBoard != nullptr)
                    {
                        qwirkleCount++;
                        score++;

                        // add point for tile neighbour
                        if (!addPointCheck)
                        {
                            addPointCheck = true;
                            score++;
                        }

                        // obtain a qwirkle
                        if (qwirkleCount == 5)
                            score += 6;

                        // check for placing next to another tile
                        if (!hasTileNeighbour)
                            hasTileNeighbour = true;

                        // get tile colour and shape
                        char tileBoardColour = tileOnBoard->getColour();
                        int tileBoardShape = tileOnBoard->getShape();

                        char tileColour = tile->getColour();
                        int tileShape = tile->getShape();

                        // (T1.colour == T2.colour || T1.shape != T2.shape) && (T1.colour != T2.colour || T1.shape == T2.shape) 
                        if ((tileBoardColour == tileColour || tileBoardShape != tileShape) && (tileBoardColour != tileColour || tileBoardShape == tileShape))
                        {
                            returnValue = false;
                        }
                    }
                } while (tileOnBoard != nullptr && returnValue);
            }
        }

        // Prevent player from placing tile unless next to existing tile
        if (boardHasTile && !hasTileNeighbour && returnValue)
            returnValue = false;
    }
    else
        returnValue = false;

    return returnValue;
}

bool Game::replaceTile(sharedPlayerPtr player, sharedTilePtr tile)
{
    // Remove the tile from the players hand
    bool canReplace = player->getPlayerHand()->removeNode(tile);

    if (canReplace)
    {
        // place tile in the tile bag
        tileBag->getList()->pushBack(tile);

        // get front tile from tilebag
        sharedTilePtr tileFromBag = tileBag->getList()->getFrontTile();
        // delete front tile from tileBag
        tileBag->getList()->removeFront();

        // add tile to the player’s hand
        player->getPlayerHand()->pushBack(tileFromBag);
    }

    return canReplace;
}

bool Game::placeTile(sharedPlayerPtr player, sharedTilePtr tile, int row, int col)
{
    bool canPlace = false;

    // if tile exists
    if (player->getPlayerHand()->tileExists(tile))
    {
        int getScore = 0;
        // placing is valid
        if (tileValidation(tile, row, col, getScore))
        {
            if (!boardHasTile)
            {
                getScore++;
                boardHasTile = true;
            }
            
            // update player score
            player->setScore(player->getCurrentScore()+getScore);

            canPlace = true;

            // remove tile from hand
            player->getPlayerHand()->removeNode(tile);

            // set tile into board
            boardEnv[col][row] = tile;

            // Check for avaliable tiles
            if (!tileBag->getList()->isEmpty())
            {
                // Get tile from tile bag
                sharedTilePtr addTile = tileBag->getList()->getFrontTile();
                tileBag->getList()->removeFront();

                // add it to the player’s hand
                player->getPlayerHand()->pushBack(addTile);
            }
        }
    }

    return canPlace;
}

void Game::saveGame(string fileName, sharedPlayerPtr player) 
{
    std::ofstream file(fileName + ".save");
	sharedPlayerPtr players[4] = {player1, player2, player3,player4};
	for (sharedPlayerPtr p : players)
	{
		file << p->getPlayerName() << endl;
		file << p->getCurrentScore() << endl;
		file << p->handToString() << endl;
	}
	file << ROW_COUNT << "," << COLUMN_COUNT << endl;
    // print board tile and position (tile@position)pla
    for (int col = 0; col < COLUMN_COUNT; col++)
    {
        for (int row = 0; row < ROW_COUNT; row++)
        {
            if (boardEnv[col][row] != nullptr)
            {
                char convertCol = col + FIX_COL+1;
                file << boardEnv[col][row]->getColour() << boardEnv[col][row]->getShape() << "@" << convertCol << row+1 << ", ";
            }
        }
    }
	file << endl;
	sharedNodePtr current = tileBag->getList()->getHead();
	while(current != nullptr)
	{
		file << current->tile->getColour() << current->tile->getShape() << ",";
		current = current->next;
	}
	file << endl;
	file << player->getPlayerName() << endl;
    file.close();

    cout << "Game Saved" << endl << endl;
}