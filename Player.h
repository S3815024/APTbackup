#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include <string>
#include <iostream>
#include "LinkedList.h"

class Player
{
public:
    // Constructor
    Player(int id, std::string name);
    Player(int id, std::string name, int score);

    // Deconstructor
    ~Player();

    // Methods
    std::string getPlayerName();
    int getPlayerID();
    int getCurrentScore();
    void setScore(int newScore);
    sharedLinkedListPtr getPlayerHand();
    std::string handToString();

private:
    // Player Variables
    int id;
    std::string name;
    sharedLinkedListPtr hand;
    int score;
};

#endif // ASSIGN2_PLAYER_H
