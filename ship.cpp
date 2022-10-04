//
// Created by hoove on 10/30/2019.
//

#include "ship.h"
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

//default contructor for Ship
Ship::Ship() : shipType(" "), fX(0), fY(0), orientation(' '), size(0), hits(0), sunk(false) {
}

//Constructor for Ship.
//pre-condition: accepts type string variable for shipType, int fX, int FY,
// and type char for orientation.
// post-condition: creates an object of Ship type with private member variables initialized to paramaters
// sets private member size to int corresponding to shipType
Ship::Ship(string type, int x, int y, char orient) : shipType(type), fX(x), fY(y), orientation(orient), hits(0), sunk(false){

    if (shipType == "Carrier"){
        size = 5;
    }
    else if(shipType == "Battleship"){
        size = 4;
    }
    else if (shipType == "Cruiser" || shipType == "Submarine"){
        size = 3;
    }
    else if(shipType == "Destroyer"){
        size = 2;
    }
}

//mutators for Ship class
void Ship::setType(string type) {
    shipType = type;
}

void Ship::setFront(int x, int y){
    fX = x;
    fY = y;
}

void Ship::setOrientation(char o) {
    orientation = o;
}

// implementation for addHit()
// pre-condition: none
//post-condition: increments private member variable hits by one
// checks to see if additional hit was enough to sink ship
//returns value of private member variable sunk
void Ship::addHit() {
    hits++;
    if (hits == size){
        sunk = true;
    }
}

bool Ship::checkSunk() {
    return sunk;
}

//accessors for Ship class

string Ship::getType() {
    return shipType;
}

int Ship::getFrontX() {
    return fX;
}

int Ship::getFrontY() {
    return fY;
}

char Ship::getOrientation() {
    return orientation;
}

int Ship::getSize() {
    return size;
}
