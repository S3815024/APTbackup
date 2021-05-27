#include "Util.h"

#include <memory>
#include <regex>

using std::shared_ptr;

using std::cin;
using std::cout;
using std::endl;

using std::regex;
using std::regex_match;

string userInput(action action)
{
    string playerInput = "";

    playerInput = recursiveInput(action, playerInput);
    
    return playerInput;
}

string recursiveInput(action action, string playerInput)
{
    bool returnValue = false;

    std::getline(cin, playerInput);

    // If input is still valid
    if (action == ADD_PLAYER)
    {
        // Check for symbols
        if (regex_match(playerInput, regex("^[A-Z]+$")))
        {
            returnValue = true;
        }
        else{
            std::cout << "Please enter your name below and characters must be only capital letters(A-Z) " << std::endl;
        }
    }
    else if (action == MENU_INPUT)
    {
        // Between 1-4 only 1 character
        if (regex_match(playerInput, regex("^[1-5]{1}$")))
        {
            returnValue = true;
        }
        else if(regex_match(playerInput, regex("^help$"))){
            std::cout <<"Enter 1 to start a new game\n"<<endl;
            std::cout <<"Enter 2 to load a saved game\n"<<endl;
            std::cout <<"Enter 3 to print game credits\n"<<endl;
            std::cout <<"Enter 4 quit game\n"<<endl;
        }
        else{
            std::cout << "Please select 1,2,3 or 4 " << std::endl;
        }
    }
    else if (action == PLAYER_TURN)
    {
        // Condition: If 1st word matches ["place"] and input does not match case ["place ## at ##"]
        if (regex_match(playerInput, regex("^place [ROYGBP]{1}[1-6]{1} at [A-Z]{1}[0-9]{1,2}$")))
        {   
            //cout << endl << "Invalid Input" << endl;
            returnValue = true;
        }
        // Condition: If 1st word matches ["replace"] and 2nd input is not tile string ["##"]
        else if (regex_match(playerInput, regex("^replace [ROYGBP]{1}[1-6]{1}$")))
        {   
            //cout << endl << "Invalid Input" << endl;
            returnValue = true;
        }
        // Condition: If 1st word matches ["help"] 
        else if (regex_match(playerInput, regex("^help$")))
        {
            //cout << "> ";
            //playerInput = recursiveInput(action, playerInput);
            returnValue = true;
        }
        // Condition: If 1st word matches ["save"] and no filename is specified
        else if(regex_match(playerInput, regex("^save [a-zA-Z0-9]+$")))
        {   
            //cout << endl << "Invalid Input" << endl;
            returnValue = true;
        }
        else{
            if(regex_match(playerInput, regex("(place)(.*)")))
            {
                std::cout << "Please enter the correct Tile in hand and place on board" << std::endl;
                std::cout << "Input as (place <tile> at <board-coordinate>)" << std::endl;
            }
            else if (regex_match(playerInput, regex("(replace)(.*)")))
            {
                
                std::cout << "Please input the correct Tile in hand " << std::endl;
                std::cout << "Input as (replace <tile>)" << std::endl;
            }
            else if (regex_match(playerInput, regex("(save)(.*)")))
            {
                std::cout << "If you want to save game write as (save <name>)" << std::endl;
            }
            else{
                std::cout << "Invalid input type (help)" << std::endl;
            }
        }
    }
    else if (action == LOAD)
    {
        if (regex_match(playerInput, regex("^[a-zA-Z0-9]+.save$")) || regex_match(playerInput, regex("^./(.*)/[a-zA-Z0-9]+.save$")))
        {
            returnValue = true;
        }
        else{
            std::cout << "Input as (<name>.save)" << std::endl;
        }
    }

    if (!returnValue)
    {
        if (!cin.eof())
        {
            cout << "> ";
            playerInput = recursiveInput(action, playerInput);
        }
        else
        {
            cout << endl << endl;
            cout << "Goodbye!" << endl;
        }
    }

    return playerInput;
}