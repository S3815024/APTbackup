#ifndef UTIL_H
#define UTIL_H

#include <iostream>

using std::string;

enum action
{
    ADD_PLAYER,
    MENU_INPUT,
    PLAYER_TURN,
    LOAD,
};

string userInput(action action);

string recursiveInput(action action, string playerInput);

#endif // UTIL_H