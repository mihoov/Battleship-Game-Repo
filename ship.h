//
// Created by hoove on 10/30/2019.
//

#ifndef PROJECT_PART_1_SHIP_H
#define PROJECT_PART_1_SHIP_H

#include <string>

using namespace std;

class Ship{
private:
    string shipType;
    int fX; // x-coordinate for front of the ship
    int fY; // y-coordinate for front of the ship
    char orientation;
    int size;
    int hits;
    bool sunk;

public:
    Ship();
    Ship(string type, int x, int y, char orient);

    void setType(string type);
    void setFront(int x, int y);
    void setOrientation(char o);
    void addHit();

    string getType();
    int getFrontX();
    int getFrontY();
    char getOrientation();
    int getSize();
    bool checkSunk();



};

#endif //PROJECT_PART_1_SHIP_H
