#include <fstream>

#include "Menu.h"
#include "Game.h"
#include "Util.h"


using std::cout;
using std::endl;
using std::make_shared;

void runMenu()
{
    bool quitMenu = false;
    std::string input = "";

    do
    {   
        printMenu();

        cout << endl << "> ";

        // convert string to integer (stoi)
        input = userInput(MENU_INPUT);
        cout << endl;

        if (input == "1")
        {
            shared_ptr<Game> game = make_shared<Game>();
            game->startGame();

            quitMenu = true;
        }
        else if (input == "2")
        {
            loadGame();
            quitMenu = true;
        }
        else if (input == "3")
        {
            printCredits();
            cout << endl;
        }
        else if (input == "4")
        {
            cout << "Goodbye!" << endl;
            quitMenu = true;
        }
        /*else if (input == "5")
        {
            //cout << "help called" <<endl;
            //cout<< "for further help in other functions type help "<<endl;
            //runMenu();
            help();
        }*/
        else if (std::cin.eof())
        {
            quitMenu = true;
        }

    } while(!quitMenu);

}
/*void help(){
    cout<< "" << endl;
}*/

void printCredits()
{
    std::cout << "---------------------------------------------" << std::endl;

    std::cout << "Name: Ahnaf Rahman Samin" << std::endl;
    std::cout << "Student ID: s3815024" << std::endl;
    std::cout << "Email: s3815024@student.rmit.edu.au" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "Name: Emanuel Le" << std::endl;
    std::cout << "Student ID: s3844780" << std::endl;
    std::cout << "Email: s3844780@student.rmit.edu.au" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "Name: Aaron Schmid" << std::endl;
    std::cout << "Student ID: s3784832" << std::endl;
    std::cout << "Email: s3784832@student.rmit.edu.au" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "Name: Wisith Halpandeniya Hevage" << std::endl;
    std::cout << "Student ID: s3728665" << std::endl;
    std::cout << "Email: s3728665@student.rmit.edu.au" << std::endl;

    std::cout << "---------------------------------------------\n" << std::endl;
}

void printMenu()
{
    std::cout << "MENU" << endl;
    std::cout << "----" << endl;
    std::cout << "1. New Game" << endl;
    std::cout << "2. Load Game" << endl;
    std::cout << "3. Credits (Show student information)" << endl;
    std::cout << "4. Quit" << endl;
}

void loadGame()
{
    cout << "Enter the filename from which load a game " << endl;
    cout << "> ";
    std::string fileName;

    std::ifstream inputFile;
    
    do
    {
        fileName = userInput(LOAD);

        inputFile.open(fileName);

        if (!inputFile.good() && !std::cin.eof())
        {
            cout << "Invalid Input" << endl;
            cout << "> ";
        }

    } while (!inputFile.good() && !std::cin.eof());

    if (!std::cin.eof())
        shared_ptr<Game> game = make_shared<Game>(inputFile);
}