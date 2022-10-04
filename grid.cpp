//
// Created by hoove on 10/30/2019.
//

#include "grid.h"
#include <fstream>
#include <iostream>
#include <iomanip>

Grid::Grid() {
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            grid[i][j] = 0;
        }
    }
}

Grid::Grid(int fill) {
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            grid[i][j] = fill;
        }
    }
}

void Grid::setGridPoint(int x, int y, int fill) {
    grid[x][y] = fill;
}

int Grid::getGridPoint(int x, int y) {
    return grid[x][y];
}
