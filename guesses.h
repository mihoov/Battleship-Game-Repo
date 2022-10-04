//
// Created by hoove on 11/26/2019.
//

#ifndef FINAL_PROJECT_GUESSES_H
#define FINAL_PROJECT_GUESSES_H

#endif //FINAL_PROJECT_GUESSES_H

#include "grid.h"
#include "shipPlacement.h"
#include <iostream>
#include <iomanip>

class Guesses : public Grid {
private:
    int newGuess[2];

public:

    Guesses();

    void setNewGuess(int x, int y);
    void getNewGuess(int* copyNewGuess);
    void userGuess() throw(QuitGame);
    void computerGuess();
    void printGuesses();
    bool checkGuess();




};