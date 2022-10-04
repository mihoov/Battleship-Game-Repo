//
// Created by hoove on 11/26/2019.
//

//
// Created by hoove on 10/30/2019.
//

#include "shipPlacement.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include<ctime>
#include<cstdlib>
#include<random>

using namespace std;



ShipPlacement::ShipPlacement() : Grid(), shipsRemaining(5), validShips(false) {}


int ShipPlacement::getShipsRemaining() {
    shipsRemaining = 5;

    if (carrier->checkSunk()){
        shipsRemaining--;
    }

    if (battleship->checkSunk()){
        shipsRemaining--;
    }

    if (cruiser->checkSunk()){
        shipsRemaining--;
    }

    if (submarine->checkSunk()){
        shipsRemaining--;
    }

    if (destroyer->checkSunk()){
        shipsRemaining--;
    }

    return shipsRemaining;
}


//mutators to set the private member variables of type Ship
void ShipPlacement::setCarrier(Ship *c) {
    carrier = c;
}

void ShipPlacement::setBattleship(Ship *b) {
    battleship = b;
}

void ShipPlacement::setCruiser(Ship *c) {
    cruiser = c;
}

void ShipPlacement::setSubmarine(Ship *s) {
    submarine = s;
}

void ShipPlacement::setDestroyer(Ship *d) {
    destroyer = d;
}


Ship* ShipPlacement::getCarrier() {
    return carrier;
}

Ship* ShipPlacement::getBattleship() {
    return battleship;
}

Ship* ShipPlacement::getCruiser() {
    return cruiser;
}

Ship* ShipPlacement::getSubmarine() {
    return submarine;
}

Ship* ShipPlacement::getDestroyer() {
    return destroyer;
}



//definition for member function readShipsFromFile
// pre-condition: reference to an open file input stream
// process: function reads information from file and checks that data is valid for the game of Battleship
// function stores the data in the ShipPlacement objects member variables. The function throws exceptions for illegal data
//post-condition: none
void ShipPlacement::readShipsFromFile(ifstream &inFile)
throw(IllegalShipType, IllegalOrientation, DuplicateShip, MissingShip, OutOfBounds) {

    string type;
    string fileFront;
    string fileOrient;
    int xCord;
    int yCord;
    char orient;
    bool gotCar = false;
    bool gotBat = false;
    bool gotCru = false;
    bool gotSub = false;
    bool gotDes = false;
    Ship *shipPtr;

    while ( getline(inFile, type, ',')){
        getline(inFile, fileFront, ',');
        getline(inFile, fileOrient);

        //determining value of x coordinate based on letter value read from file
        if(fileFront[0] == 'A'){
            xCord = 0;
        }
        else if(fileFront[0] == 'B'){
            xCord = 1;
        }
        else if(fileFront[0] == 'C'){
            xCord = 2;
        }
        else if(fileFront[0] == 'D'){
            xCord = 3;
        }
        else if(fileFront[0] == 'E'){
            xCord = 4;
        }
        else if(fileFront[0] == 'F'){
            xCord = 5;
        }
        else if(fileFront[0] == 'G'){
            xCord = 6;
        }
        else if(fileFront[0] == 'H'){
            xCord = 7;
        }
        else if(fileFront[0] == 'I'){
            xCord =8;
        }
        else if(fileFront[0] == 'J'){
            xCord = 9;
        }
        else {
            // throws exception if the front coordinate of ship is invalid
            throw OutOfBounds();
        }

        fileFront.erase(0,1);
        yCord = stoi(fileFront);
        yCord--;

        if (  (yCord < 0) || (yCord > 9)){
            // throws exception if the front coordinate of ship is invalid
            throw OutOfBounds();
        }


        orient = fileOrient[0];
        if ((orient != 'H') && (orient != 'V'))
        {
            //throws exception if orientation value from file is not a valid value
            throw IllegalOrientation();
        }

        //creates a new Ship object with inputs from file and assigns the pointer to it
        shipPtr = new Ship(type, xCord, yCord, orient);


        //checking to see which type of ship was read in from the file
        //and recording that the ship was received with bool value
        if (type == "Carrier"){
            if (!gotCar) {
                setCarrier(shipPtr);
                gotCar = true;
            }
            else {
                // throws exception if Carrier was already read from file
                throw DuplicateShip();
            }
        }
        else if (type == "Battleship"){
            if(!gotBat) {
                setBattleship(shipPtr);
                gotBat = true;
            }
            else{
                // throws exception if battleship was already read from file
                throw DuplicateShip();
            }
        }
        else if (type == "Cruiser"){
            if(!gotCru) {
                setCruiser(shipPtr);
                gotCru = true;
            }
            else {
                // throws exception if battleship was already read from file
                throw DuplicateShip();
            }
        }
        else if (type == "Submarine"){
            if (!gotSub) {
                setSubmarine(shipPtr);
                gotSub = true;
            }
            else {
                // throws exception if submarine was already read from file
                throw DuplicateShip();
            }
        }
        else if (type == "Destroyer"){
            if (!gotDes) {
                setDestroyer(shipPtr);
                gotDes = true;
            }
            else {
                // throws exception if destroyer was already read from file
                throw DuplicateShip();
            }
        }
        else{
            //throws exception if shipType read from file is not 1 of 5 valid types
            throw IllegalShipType();
        }


    }

    if (( gotCar==false) || (gotBat==false) || (gotCru==false) || (gotSub==false) || (gotDes==false)){
        //throws exception if 5 unique ships types were not read from file
        throw MissingShip();
    }

    // code for testing
    /* cout << endl << "carrier: " << carrier->getFrontX() << " , " << carrier->getFrontY();
     cout << endl << "battleship: " << battleship->getFrontX() << " , " << battleship->getFrontY();
     cout << endl << "cruiser: " << cruiser->getFrontX() << " , " << cruiser->getFrontY();
     cout << endl << "submarine: " << submarine->getFrontX() << " , " << submarine->getFrontY();
     cout << endl << "destroyer: " << destroyer->getFrontX() << " , " << destroyer->getFrontY();
 */

} // end readShipsFromFile


//function definition for placeOneShipOnGrid
//precondition: a pointer to an object of type Ship
//process: the function marks the grid for the location of the ship.
// It throws exceptions if the data is illegal
//postcondition: none
void ShipPlacement::placeOneShipOnGrid(Ship *aShip) throw (ShipOverlap, OutOfBounds){

    int x;
    int y;
    int fill;

    //cout << aShip->getType() << endl;
    x = aShip->getFrontX();
    //cout << "x value: " << x << "  " << x + aShip->getSize()-1 <<  endl;
    y = aShip->getFrontY();
    //cout << "y value: " << y <<" " << y + aShip->getSize()-1 <<  endl;
    //cout << "orientation: " << aShip->getOrientation() << endl;

    //function will place an int value on grid points occupied by a ship
    // 1 for Carrier
    // 2 for Battleship
    // 3 for Cruiser
    // 4 for Submarine
    // 5 for Destroyer
    if (aShip->getType() == "Carrier"){
        fill = 1;
    }
    else if (aShip->getType() == "Battleship"){
        fill = 2;
    }
    else if (aShip->getType() == "Cruiser"){
        fill = 3;
    }
    else if (aShip->getType() == "Submarine"){
        fill = 4;
    }
    else if (aShip->getType() == "Destroyer"){
        fill = 5;
    }

    //begin if statement for horizontal orientation
    if (aShip->getOrientation() == 'H'){
        if ((x + aShip->getSize()) > 10){
            //throws exception if ship goes out of bounds
            throw OutOfBounds();
        }
        for (int i = 0; i < aShip->getSize(); i++) {
            if ( 0 == getGridPoint(x+i, y)){
                setGridPoint(x+i, y, fill);
            }
            else {
                //throws exception if more than one ship is occupying the same point on the grid
                throw ShipOverlap();
            }
        }

    }// end if statement for vertical orientation
    else if (aShip->getOrientation() == 'V'){
        if ((y + aShip->getSize()) > 10){
            //throws exception if ship goes out of bounds
            throw OutOfBounds();
        }
        for (int i = 0; i < aShip->getSize(); i++) {
            if ( 0 == getGridPoint(x, y+i)){
                setGridPoint(x, y+i, fill);
            }
            else {
                //throws exception if more than one ship is occupying the same point on the grid
                throw ShipOverlap();
            }
        }
    }// end if statement for vertical orientation
}// end placeOneShipOnGrid definition



//function definition for placeShipsOnGrid
// a public member function of ShipPlacement
// pre-condition: valid Ship type variables have been placed in ShipPlacement class
// process: function reads information from private members and marks the grid for the location of the ships
// It will throw exceptions from illegally placed ships
// post-condition: none
void ShipPlacement::placeShipsOnGrid() throw(ShipOverlap, OutOfBounds) {

    placeOneShipOnGrid(carrier);
    placeOneShipOnGrid(battleship);
    placeOneShipOnGrid(cruiser);
    placeOneShipOnGrid(submarine);
    placeOneShipOnGrid(destroyer);

}// end placeShipsOnGrid definition

//function definition for printShipGrid
//pre-condition: none
//process: The function reads the private member variables and outputs a grid to the screen
// that displays the placement of the ships
//post-condition: none
void ShipPlacement::printShipPlacement() {
    cout << endl << "C = Carrier  B = Battleship  R = Cruiser  S = Submarine  D = Destroyer  O = miss  X = hit" << endl << endl;
    cout << setfill(' ') << "      A    B    C    D    E    F    G    H    I    J" << endl;
    for (int y = 0; y < 10; y++){
        cout << setw(2) << y+1;
        for (int x = 0; x < 10; x++){
            switch(getGridPoint(x, y)){
                case 0:
                    cout << "    -";
                    break;
                case 1:
                    cout << "    C";
                    break;
                case 2:
                    cout << "    B";
                    break;
                case 3:
                    cout << "    R";
                    break;
                case 4:
                    cout << "    S";
                    break;
                case 5:
                    cout << "    D";
                    break;
                case 6:
                    cout << "    O";
                    break;
                case 7:
                    cout << "    X";
                    break;
            }
        }
        cout << endl;
    }


    /*
    cout << "Carrier: (" << carrier->getFrontX() << "," << carrier->getFrontY()  << ")  " << carrier->getOrientation()
         << "   " << carrier->getSize() << endl;
    cout << "Battleship: (" << battleship->getFrontX() << "," << battleship->getFrontY()  << ")  " << battleship->getOrientation()
         << "   " << battleship->getSize() << endl;
    cout << "Cruiser: (" << cruiser->getFrontX() << "," << cruiser->getFrontY()  << ")  " << cruiser->getOrientation()
         << "   " << cruiser->getSize() << endl;
    cout << "Submarine: (" << submarine->getFrontX() << "," << submarine->getFrontY()  << ")  " << submarine->getOrientation()
         << "   " << submarine->getSize() << endl;
    cout << "Destroyer: (" << destroyer->getFrontX() << "," << destroyer->getFrontY()  << ")  " << destroyer->getOrientation()
         << "   " << destroyer->getSize() << endl;
         */

}// end definition of printShipPlacement

//definition for randomShips
//precondition: none
//process: the function randomly places 5 ships on the grid for the computer player
//postcondition: none
void ShipPlacement::randomShips() {

    Ship *aShip;
    string type;
    int x, y, orNum;
    char orient;
    bool validShip;

    //begin for loop to run 5 times, once for each type of ship
    for (int i = 0; i < 5; i++){

        validShip = false;

        //begin while loop to find valid ship placement
        while(!validShip) {

            validShip = true;

            int x = rand() % 10;
            int y = rand() % 10;
            orNum = rand() % 2;
            if (orNum == 0) {
                orient = 'H';
            } else {
                orient = 'V';
            }
            switch (i) {
                case 0:
                    type = "Carrier";
                    break;
                case 1:
                    type = "Battleship";
                    break;
                case 2:
                    type = "Cruiser";
                    break;
                case 3:
                    type = "Submarine";
                    break;
                case 4:
                    type = "Destroyer";
                    break;
            }

            aShip = new Ship(type, x, y, orient);
            try {
                placeOneShipOnGrid(aShip);
            }
            catch (ShipOverlap) {
                validShip = false;
                delete aShip;
                aShip = nullptr;

                //loop to reset grid points that may have been invalidly set
                for (int p = 0; p < 10; p++){
                    for (int q = 0; q < 10; q++){
                        if (getGridPoint(p, q) == i+1){
                            setGridPoint(p, q, 0);
                        }
                    }
                }

            }
            catch (OutOfBounds) {
                validShip = false;
                delete aShip;
                aShip = nullptr;

                //loop to reset grid points that may have been invalidly set
                for (int p = 0; p < 10; p++){
                    for (int q = 0; q < 10; q++){
                        if (getGridPoint(p, q) == i+1){
                            setGridPoint(p, q, 0);
                        }
                    }
                }
            }

        }// end while loop

        switch (i) {
            case 0:
                setCarrier(aShip);
                break;
            case 1:
                setBattleship(aShip);
                break;
            case 2:
                setCruiser(aShip);
                break;
            case 3:
                setSubmarine(aShip);
                break;
            case 4:
                setDestroyer(aShip);
                break;
        }
    } // end for loop
} // end randomShips() function