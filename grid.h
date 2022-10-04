//
// Created by hoove on 10/30/2019.
//

#ifndef PROJECT_PART_1_CLASSES_H
#define PROJECT_PART_1_CLASSES_H

#include<string>

using namespace std;

class OutOfBounds {};
class ShipOverlap {};
class IllegalShipType {};
class IllegalOrientation {};
class DuplicateShip{};
class MissingShip{};
class QuitGame{};
class Grid {
private:
    int grid[10][10];

public:
    Grid();
    Grid(int fill);

    void setGridPoint(int x, int y, int fill);
    int getGridPoint(int x, int y);
};

#endif //PROJECT_PART_1_CLASSES_H
