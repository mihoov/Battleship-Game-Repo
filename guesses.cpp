//
// Created by hoove on 11/26/2019.
//

#include "guesses.h"



Guesses::Guesses() : Grid() {
    //intentionally left blank
}

//--------getNewGuess--------
void Guesses::getNewGuess(int* copyNewGuess) {
    copyNewGuess[0] = newGuess[0];
    copyNewGuess[1] = newGuess[1];
}

//--------setNewGuess--------
void Guesses::setNewGuess(int x, int y) {
    newGuess[0] = x;
    newGuess[1] = y;
}

//--------userGuess--------
void Guesses::userGuess() throw (QuitGame){

    string userInput;
    int yCord;
    bool done;
    bool outerLoopDone;

    cout << "Your turn." << endl;

    do {
        outerLoopDone = true;
        do {

            done = true;

            //get the user guess from keyboard input
            cout << "Enter your shot or enter 'Q' to quit game:";
            getline(cin, userInput);

            //convert the letter of the guess into a number for the x coordinate
            if (userInput[0] == 'A' || userInput[0] == 'a') {
                newGuess[0] = 0;
            }
            else if (userInput[0] == 'B' || userInput[0] == 'b') {
                newGuess[0] = 1;
            }
            else if (userInput[0] == 'C' || userInput[0] == 'c') {
                newGuess[0] = 2;
            }
            else if (userInput[0] == 'D' || userInput[0] == 'd') {
                newGuess[0] = 3;
            }
            else if (userInput[0] == 'E' || userInput[0] == 'e') {
                newGuess[0] = 4;
            }
            else if (userInput[0] == 'F' || userInput[0] == 'f') {
                newGuess[0] = 5;
            }
            else if (userInput[0] == 'G' || userInput[0] == 'g') {
                newGuess[0] = 6;
            }
            else if (userInput[0] == 'H' || userInput[0] == 'h') {
                newGuess[0] = 7;
            }
            else if (userInput[0] == 'I' || userInput[0] == 'i') {
                newGuess[0] = 8;
            }
            else if (userInput[0] == 'J' || userInput[0] == 'j') {
                newGuess[0] = 9;
            }
            else if(userInput[0] == 'Q' || userInput[0] == 'q') {
                throw QuitGame();
            }
            //output an error to the screen if the user did not enter a valid letter
            // set done to false to the loop repeats
            else {
                cout << "Error: illegal shot." << endl;
                cout << "Be sure to enter a letter(A-J) for the first character of your shot." << endl;
                cout << " Example: F3" << endl << endl;
                done = false;
            }

            if (done) {
                userInput.erase(0, 1);

                if (userInput.size() < 1){
                    done = false;
                    cout << "Error: illegal shot." << endl;
                    cout << "Be sure to enter a number for the second part of your shot" << endl << endl;
                }
                else {
                    yCord = stoi(userInput);
                    yCord--;

                    if (yCord >= 0 && yCord <= 9) {
                        newGuess[1] = yCord;
                    } else {
                        cout << "Error: illegal shot." << endl;
                        cout << "Be sure to enter an integer(1-10) for the second character of your shot." << endl;
                        cout << "Example: H7" << endl << endl;
                        done = false;
                    }
                }
            }

        } while (!done);


        if(!checkGuess()){
            cout << "You have already guessed that coordinate. Guess again." << endl;
            outerLoopDone = false;
        }
    }while (!outerLoopDone);
}// end userGuess


void Guesses::computerGuess() {
    int x, y;

    do {

        x = rand() % 10;
        y = rand() % 5;

        newGuess[0] = x;
        if ((x%2) == 0){
            newGuess[1] = (2*y)+1;
        }
        else{
            newGuess[1] = 2*y;
        }
    } while (!checkGuess());
}


//--------checkGuess--------
//post-condition: returns true if the coordinate has NOT already been guessed
// returns false if the the coordinate has been guessed and the guess is a duplicate, i.e. an invalid guess
bool Guesses::checkGuess() {
    bool returnValue;

    if (getGridPoint(newGuess[0], newGuess[1]) > 0){
        returnValue = false;
    }
    else{
        returnValue = true;
        setGridPoint(newGuess[0], newGuess[1], 1);
    }

    return returnValue;
} // end of checkGuess


//--------printGuesses--------
void Guesses::printGuesses() {
    cout << "Player guess grid" << endl;
    cout << endl << "O = miss  X = hit" << endl << endl;
    cout << setfill(' ') << "      A    B    C    D    E    F    G    H    I    J" << endl;
    for (int y = 0; y < 10; y++){
        cout << setw(2) << y+1;
        for (int x = 0; x < 10; x++){
            switch(getGridPoint(x, y)){
                case 0:
                    cout << "    -";
                    break;
                case 1:
                    cout << "    O";
                    break;
                case 2:
                    cout << "    X";
                    break;
            }
        }
        cout << endl;
    }
}
