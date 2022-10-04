#include <iostream>
#include<string>
#include<random>
#include <cstdlib>
#include<ctime>
#include"grid.h"
#include "ship.h"
#include "shipPlacement.h"
#include "player.h"
#include<fstream>


using namespace std;

int main() {

    srand(time(nullptr));

    ifstream inFile;
    string fileName;

    Player user(true), computer(false);


    cout << endl << endl <<"Enter name of file with Player ship placement(example: ship_placement1_good.csv): ";
    getline (cin, fileName);
    inFile.open(fileName);

    while (!inFile.is_open()){
        cout << endl << "ERROR! Could not open file: " << fileName;
        cout << endl << "Please enter a valid file name: ";
        getline(cin, fileName);
        inFile.open(fileName);
    }



    //read player's ship placement from file
    try {
        user.getShipPlacement()->readShipsFromFile(inFile);
    }
        //throw list for readShipsFromFile (IllegalShipType, IllegalOrientation, DuplicateShip, MissingShip, OutOfBounds)
        //catch blocks for the exceptions
    catch(IllegalShipType){
        cout << "The file for player ship placement contained an illegal ship type" << endl <<
             "Terminating program" << endl;
        terminate();
    }
    catch(IllegalOrientation){
        cout << "The file for player ship placement contained an illegal ship orientation" << endl <<
             "Terminating program" << endl;
        terminate();
    }
    catch(DuplicateShip){
        cout << "The contained duplicate ships" << endl <<
             "Terminating program" << endl;
        terminate();
    }
    catch(MissingShip) {
        cout << "The file for player ship placement was missing a ship type" << endl <<
             "Terminating program" << endl;
        terminate();
    }
    catch(OutOfBounds){
        cout << "The file for player ship placement attempted to place a ship out of bounds" << endl <<
             "Terminating program" << endl;
        terminate();
    }

    //place player's ships on the grid
    try{
        user.getShipPlacement()->placeShipsOnGrid();
    }

        //catch blocks for the exceptions
    catch(ShipOverlap){
        cout << "The file attempts to place ships so that more than one ship occupies the same point on the grid" << endl
             << "Terminating program" << endl;
        terminate();
    }
    catch(OutOfBounds){
        cout << "The file for player ship placement attempted to place a ship out of bounds" << endl <<
             "Terminating program" << endl;
        terminate();
    }


    //outputting player ship placement to screen
    cout << endl << endl << "Player Ship Placement" << endl;
    user.getShipPlacement()->printShipPlacement();
    cout << endl << endl << endl;

    //calling functions to randomly generate computer ship placement
    computer.getShipPlacement()->randomShips();

    // take these two lines out of comments to display the computer ships at the beginning for grading
   //cout << endl << endl << "The placement of the opponent ships" << endl;
   //computer.getShipPlacement()->printShipPlacement();

   try {
       //begin loop to play game
       while (!user.getWinCondition() && !computer.getWinCondition()) {

           user.getGuesses()->printGuesses();
           user.takeTurn(computer);

           if (!user.getWinCondition()) {
               computer.takeTurn(user);
               user.getShipPlacement()->printShipPlacement();
               cout << endl;
           }

       }

       if (user.getWinCondition()) {
           cout << "Congratulation! You are Victorious!!!" << endl << endl;
       } else {
           cout << "You Lost. Better luck next time." << endl << endl;
       }
   }

   catch(QuitGame){
       cout << "Quitting Game" << endl;
       terminate();
   }


    //outputting computer ship placement to screen
    cout << endl << endl << "The placement of the opponent ships" << endl;
    computer.getShipPlacement()->printShipPlacement();


    return 0;
}