#include "Player.h"
#include "Util.h"

// Constructor
Player::Player(int id, std::string name)
{
    this->id = id;
    this->name = name;
    hand = std::make_shared<LinkedList>();
    score = 0;
}

Player::Player(int id, std::string name, int score)
{
    this->id = id;
    this->name = name;
    this->score = score;
    hand = std::make_shared<LinkedList>();
}

// Deconstructor
Player::~Player() {}

// Returns the player's name
std::string Player::getPlayerName()
{
    return name;
}

// Returns the player's ID
int Player::getPlayerID()
{
    return id;
}

// Gets the player's current score
int Player::getCurrentScore()
{
    return score;
}

// Set player's score
void Player::setScore(int newScore)
{
    score = newScore;
}

// Returns the player's current hand
sharedLinkedListPtr Player::getPlayerHand()
{
    return hand;
}

// Prints out the player's current hand
std::string Player::handToString()
{
    return hand->listToString();
}
