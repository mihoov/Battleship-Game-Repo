//
// Created by hoove on 10/30/2019.
//

#ifndef PROJECT_PART_1_SHIPPLACEMENT_H
#define PROJECT_PART_1_SHIPPLACEMENT_H

#include<string>

#include "grid.h"
#include "ship.h"

using namespace std;

class ShipPlacement : public Grid {
private:
    int shipsRemaining;
    bool validShips;
    Ship* carrier;
    Ship* battleship;
    Ship* cruiser;
    Ship* submarine;
    Ship* destroyer;

public:
    ShipPlacement();

    int getShipsRemaining();

    void setCarrier(Ship *c);
    void setBattleship(Ship *b);
    void setCruiser(Ship *c);
    void setSubmarine(Ship *s);
    void setDestroyer(Ship *d);

    Ship* getCarrier();
    Ship* getBattleship();
    Ship* getCruiser();
    Ship* getSubmarine();
    Ship* getDestroyer();

    void readShipsFromFile(ifstream &inFile) throw(IllegalShipType, IllegalOrientation, DuplicateShip, MissingShip, OutOfBounds);
    void placeShipsOnGrid() throw (ShipOverlap, OutOfBounds);
    void placeOneShipOnGrid(Ship *aShip) throw (ShipOverlap, OutOfBounds);
    void printShipPlacement();
    void randomShips();

};

#endif //PROJECT_PART_1_SHIPPLACEMENT_H
