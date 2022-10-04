//
// Created by hoove on 11/29/2019.
//

#include "player.h"


//--------Player--------
//constructor for Player class
// Default constructor intentionally omitted because an object of Player class should never
// be created without specifying whether it is a human player or a computer player
Player::Player(bool humPlay) : humanPlayer(humPlay), winCondition(false) {
    hitsCarrierHP = nullptr;
    hitsBattleshipHP = nullptr;
    hitsCruiserHP = nullptr;
    hitsSubmarineHP = nullptr;
    hitsDestroyerHP = nullptr;
}

//--------getWinCondition--------
//post-condition: returns value of private variable 'winCondition'
bool Player::getWinCondition() {
    return winCondition;
}// end getWinCondition

//--------setWinCondition--------
//pre-condtion: accepts a reference to an object of class Player
//process: if all of the opponents ships have been sunk then the function sets winCondition to true
void Player::setWinCodntion(Player &opponent) {

    if (opponent.getShipPlacement()->getShipsRemaining() == 0)
    {
        winCondition = true;
    }
    else{
        winCondition = false;
    }

}// end setWinCondition

//--------getGuesses--------
Guesses* Player::getGuesses() {
    return &playerGuesses;
}

//--------getShipPlacement--------
ShipPlacement* Player::getShipPlacement() {
    return &playerShipPlacement;
}
//--------takeTurn--------
void Player::takeTurn(Player &opponentPlayer) throw(QuitGame) {

    bool hit;

    //if object is a human player then call function to prompt user for a guess
    if (humanPlayer){
        getGuesses()->userGuess();
    }
    //if object is a computer player then call function to generate computer guess
    else{
        compGuessDecision();
    }

    //check to see if the guess was a hit
    checkHit(opponentPlayer);

    setWinCodntion(opponentPlayer);
}


//--------checkHit-------
//pre-condition: reference to opponent Player object
// process: checks to see if the guess hit opponent ship
void Player::checkHit(Player &opponentPlayer) {

    int newGuess[2];
    compHit *currPtr = nullptr;

    getGuesses()->getNewGuess(newGuess);

    if (humanPlayer) {
        cout << "You guessed: ";
    } else {
        cout << "The computer guessed: ";
    }

    //display the guess to the screen
    switch (newGuess[0]) {
        case 0: {
            cout << "A";
            break;
        }
        case 1: {
            cout << "B";
            break;
        }
        case 2: {
            cout << "C";
            break;
        }
        case 3: {
            cout << "D";
            break;
        }
        case 4: {
            cout << "E";
            break;
        }
        case 5: {
            cout << "F";
            break;
        }
        case 6: {
            cout << "G";
            break;
        }
        case 7: {
            cout << "H";
            break;
        }
        case 8: {
            cout << "I";
            break;
        }
        case 9: {
            cout << "J";
            break;
        }
    }// end scope of switch

    cout << newGuess[1] + 1 << endl;

    //check to see if the guess hit a ship and display hit or miss to screen
    switch (opponentPlayer.getShipPlacement()->getGridPoint(newGuess[0], newGuess[1])) {
        case 0: {
            cout << "It was a miss." << endl << endl;
            if (!humanPlayer) {
                opponentPlayer.getShipPlacement()->setGridPoint(newGuess[0], newGuess[1], 6);
            }
            break;
        }
        case 1: {
            if (humanPlayer) {
                cout << "You hit the enemy Carrier!" << endl << endl;

            } else {
                cout << "The enemy hit your Carrier!" << endl << endl;
                opponentPlayer.getShipPlacement()->setGridPoint(newGuess[0], newGuess[1], 7);

                if (hitsCarrierHP == nullptr) {
                    hitsCarrierHP = new compHit;
                    hitsCarrierHP->hitCoord[0] = newGuess[0];
                    hitsCarrierHP->hitCoord[1] = newGuess[1];
                    hitsCarrierHP->next = nullptr;
                }
                else {
                    currPtr = new compHit;
                    currPtr->hitCoord[0] = newGuess[0];
                    currPtr->hitCoord[1] = newGuess[1];

                    currPtr->next = hitsCarrierHP;
                    hitsCarrierHP = currPtr;
                    currPtr = nullptr;
                }
            }
            //add a hit to the opponent carrier
            opponentPlayer.getShipPlacement()->getCarrier()->addHit();

            //mark the hit on the guess grid
            getGuesses()->setGridPoint(newGuess[0], newGuess[1], 2);

            //when a carrier is hit, check to see it it was sunk
            //if it's sunk then display it to screen.
            if (opponentPlayer.getShipPlacement()->getCarrier()->checkSunk()) {
                if (humanPlayer) {
                    cout << "You sunk the enemy Carrier!" << endl << endl;
                } else {
                    cout << "The enemy sunk your Carrier!" << endl << endl;
                }
            }

            break;
        }
        case 2: {
            if (humanPlayer) {
                cout << "You hit the enemy Battleship!" << endl << endl;

            }
            else {
                cout << "The enemy hit your Battleship" << endl << endl;
                opponentPlayer.getShipPlacement()->setGridPoint(newGuess[0], newGuess[1], 7);

                if (hitsBattleshipHP == nullptr) {
                    hitsBattleshipHP = new compHit;
                    hitsBattleshipHP->hitCoord[0] = newGuess[0];
                    hitsBattleshipHP->hitCoord[1] = newGuess[1];
                    hitsBattleshipHP->next = nullptr;
                }
                else {
                    currPtr = new compHit;
                    currPtr->hitCoord[0] = newGuess[0];
                    currPtr->hitCoord[1] = newGuess[1];

                    currPtr->next = hitsBattleshipHP;
                    hitsBattleshipHP = currPtr;
                    currPtr = nullptr;
                }
            }
            //add hit to opponent battleship
            opponentPlayer.getShipPlacement()->getBattleship()->addHit();

            //mark the hit on the guess grid
            getGuesses()->setGridPoint(newGuess[0], newGuess[1], 2);

            //when a battleship is hit, check to see it it was sunk
            //if it's sunk then display it to screen.
            if (opponentPlayer.getShipPlacement()->getBattleship()->checkSunk()) {
                if (humanPlayer) {
                    cout << "You sunk the enemy Battleship!" << endl << endl;
                } else {
                    cout << "The enemy sunk your Battleship!" << endl << endl;
                }
            }
            break;
        }
        case 3: {
            if (humanPlayer) {
                cout << "You hit the enemy Cruiser!" << endl << endl;

            } else {
                cout << "The enemy hit your Cruiser!" << endl << endl;
                opponentPlayer.getShipPlacement()->setGridPoint(newGuess[0], newGuess[1], 7);

                if (hitsCruiserHP == nullptr) {
                    hitsCruiserHP = new compHit;
                    hitsCruiserHP->hitCoord[0] = newGuess[0];
                    hitsCruiserHP->hitCoord[1] = newGuess[1];
                    hitsCruiserHP->next = nullptr;
                } else {
                    currPtr = new compHit;
                    currPtr->hitCoord[0] = newGuess[0];
                    currPtr->hitCoord[1] = newGuess[1];

                    currPtr->next = hitsCruiserHP;
                    hitsCruiserHP = currPtr;
                    currPtr = nullptr;
                }
            }
            //add hit to opponent cruiser
            opponentPlayer.getShipPlacement()->getCruiser()->addHit();

            //mark the hit on the guess grid
            getGuesses()->setGridPoint(newGuess[0], newGuess[1], 2);

            //when a carrier is hit, check to see it it was sunk
            //if it's sunk then display it to screen.
            if (opponentPlayer.getShipPlacement()->getCruiser()->checkSunk()) {
                if (humanPlayer) {
                    cout << "You sunk the enemy Cruiser!" << endl << endl;
                } else {
                    cout << "The enemy sunk your Cruiser!" << endl << endl;
                }
            }
            break;
        }
        case 4: {
            if (humanPlayer) {
                cout << "You hit the enemy Submarine!" << endl << endl;

            } else {
                cout << "The enemy hit your Submarine!" << endl << endl;
                opponentPlayer.getShipPlacement()->setGridPoint(newGuess[0], newGuess[1], 7);

                if (hitsSubmarineHP == nullptr) {
                    hitsSubmarineHP = new compHit;
                    hitsSubmarineHP->hitCoord[0] = newGuess[0];
                    hitsSubmarineHP->hitCoord[1] = newGuess[1];
                    hitsSubmarineHP->next = nullptr;
                } else {
                    currPtr = new compHit;
                    currPtr->hitCoord[0] = newGuess[0];
                    currPtr->hitCoord[1] = newGuess[1];

                    currPtr->next = hitsSubmarineHP;
                    hitsSubmarineHP = currPtr;
                    currPtr = nullptr;
                }

            }
            //add hit to opponent submarine
            opponentPlayer.getShipPlacement()->getSubmarine()->addHit();

            //mark the hit on the guess grid
            getGuesses()->setGridPoint(newGuess[0], newGuess[1], 2);

            //when a carrier is hit, check to see it it was sunk
            //if it's sunk then display it to screen.
            if (opponentPlayer.getShipPlacement()->getSubmarine()->checkSunk()) {
                if (humanPlayer) {
                    cout << "You sunk the enemy Submarine!" << endl << endl;
                } else {
                    cout << "The enemy sunk your Submarine!" << endl << endl;
                }
            }
            break;
        }
        case 5: {
            if (humanPlayer) {
                cout << "You hit the enemy Destroyer!" << endl << endl;

            }
            else {
                cout << "The enemy hit your Destroyer!" << endl << endl;
                opponentPlayer.getShipPlacement()->setGridPoint(newGuess[0], newGuess[1], 7);

                if (hitsDestroyerHP == nullptr) {
                    hitsDestroyerHP = new compHit;
                    hitsDestroyerHP->hitCoord[0] = newGuess[0];
                    hitsDestroyerHP->hitCoord[1] = newGuess[1];
                    hitsDestroyerHP->next = nullptr;
                } else {
                    currPtr = new compHit;
                    currPtr->hitCoord[0] = newGuess[0];
                    currPtr->hitCoord[1] = newGuess[1];

                    currPtr->next = hitsDestroyerHP;
                    hitsDestroyerHP = currPtr;
                    currPtr = nullptr;
                }
            }

            //add hit to opponent destroyer
            opponentPlayer.getShipPlacement()->getDestroyer()->addHit();

            //mark the hit on the guess grid
            getGuesses()->setGridPoint(newGuess[0], newGuess[1], 2);

            //when a carrier is hit, check to see it it was sunk
            //if it's sunk then display it to screen.
            if (opponentPlayer.getShipPlacement()->getDestroyer()->checkSunk()) {
                if (humanPlayer) {
                    cout << "You sunk the enemy Destroyer!" << endl << endl;
                }
                else {
                    cout << "The enemy sunk your Destroyer!" << endl << endl;
                }
            }
            break;
        }
    }
}


//--------compGuessDecision--------
void Player::compGuessDecision(){
    bool prevHit = false;
    bool done;
    int newGuess[2];
    int randomNum;
    compHit *currPtr = nullptr;
    compHit *searchPtr = nullptr;
    int count;

    srand(time(nullptr));

    //if there are previous hits on the enemy carrier
    if (hitsCarrierHP != nullptr) {
        count = 1;
        currPtr = hitsCarrierHP;

        while (currPtr->next != nullptr) {
            currPtr = currPtr->next;
            count++;
        }

        // if statement to execute if the carrier is not sunk
        if (count < 5) {

            // if statement executes if there is more than one hit on the carrier
            if (count > 1) {

                done = false;
                //if ship is aligned vertically
                if (hitsCarrierHP->hitCoord[0] == currPtr->hitCoord[0]) {

                    currPtr = hitsCarrierHP;
                    searchPtr = hitsCarrierHP;

                    //find hit with largest y coordinate
                    for (int j = 1; j < count; j++) {
                        searchPtr = searchPtr->next;
                        if (currPtr->hitCoord[1] < searchPtr->hitCoord[1]) {
                            currPtr = searchPtr;
                        }
                    }

                    //add 1 to the largest y coordinate and check if it is a valid guess
                    if ((currPtr->hitCoord[1] + 1) <= 9) {
                        getGuesses()->setNewGuess(currPtr->hitCoord[0], currPtr->hitCoord[1] + 1);
                        if (getGuesses()->checkGuess()) {
                            done = true;
                            prevHit = true;
                        }
                    }

                    if (!done) {

                        currPtr = hitsCarrierHP;
                        searchPtr = hitsCarrierHP;

                        //find hit with the smallest y coordinate
                        for (int j = 1; j < count; j++) {
                            searchPtr = searchPtr->next;
                            if (currPtr->hitCoord[1] > searchPtr->hitCoord[1]) {
                                currPtr = searchPtr;
                            }
                        }

                        //subtract 1 from smallest y coordinate and check if it is a valid guess
                        if ((currPtr->hitCoord[1] - 1) >= 0) {
                            getGuesses()->setNewGuess(currPtr->hitCoord[0], currPtr->hitCoord[1] - 1);
                            if (getGuesses()->checkGuess()){
                                done = true;
                                prevHit = true;
                            }
                        }
                    }
                }// end scope of vertical case

                //if ship is aligned horizontally
                else {

                    currPtr = hitsCarrierHP;
                    searchPtr = hitsCarrierHP;

                    //find hit with largest x coordinate
                    for (int j = 1; j < count; j++) {
                        searchPtr = searchPtr->next;
                        if (currPtr->hitCoord[0] < searchPtr->hitCoord[0]) {
                            currPtr = searchPtr;
                        }
                    }

                    //add 1 to the largest x coordinate and check if it is a valid guess
                    if ((currPtr->hitCoord[0] + 1) <= 9) {
                        getGuesses()->setNewGuess(currPtr->hitCoord[0] +1 , currPtr->hitCoord[1]);
                        if (getGuesses()->checkGuess()) {
                            done = true;
                            prevHit = true;
                        }
                    }

                    if (!done) {

                        currPtr = hitsCarrierHP;
                        searchPtr = hitsCarrierHP;

                        //find hit with the smallest x coordinate
                        for (int j = 1; j < count; j++) {
                            searchPtr = searchPtr->next;
                            if (currPtr->hitCoord[0] > searchPtr->hitCoord[0]) {
                                currPtr = searchPtr;
                            }
                        }

                        //subtract 1 from smallest x coordinate and check if it is a valid guess
                        if ((currPtr->hitCoord[0] - 1) >= 0) {
                            getGuesses()->setNewGuess(currPtr->hitCoord[0] - 1, currPtr->hitCoord[1]);

                            if (getGuesses()->checkGuess()){
                                done = true;
                                prevHit = true;
                            }
                        }
                    }
                } // end case for enemy ship with horizontal orientation
            }//end case for enemy ship with more than one hit

            // else statement executes if there is only 1 hit on the carrier
            else {
                done = false;
                while (!done) {
                    randomNum = rand() % 4;

                    switch (randomNum) {
                        case 0: {
                            newGuess[0] = hitsCarrierHP->hitCoord[0];
                            newGuess[1] = hitsCarrierHP->hitCoord[1] + 1;
                            break;
                        }
                        case 1: {
                            newGuess[0] = hitsCarrierHP->hitCoord[0] + 1;
                            newGuess[1] = hitsCarrierHP->hitCoord[1];
                            break;
                        }
                        case 2: {
                            newGuess[0] = hitsCarrierHP->hitCoord[0];
                            newGuess[1] = hitsCarrierHP->hitCoord[1] - 1;
                            break;
                        }
                        case 3: {
                            newGuess[0] = hitsCarrierHP->hitCoord[0] - 1;
                            newGuess[1] = hitsCarrierHP->hitCoord[1];
                            break;
                        }
                    }// end switch

                    if ((newGuess[0] <= 9) && (newGuess[0] >= 0) && (newGuess[1] <= 9) && (newGuess[1] >= 0)) {

                        getGuesses()->setNewGuess(newGuess[0], newGuess[1]);

                        if (getGuesses()->checkGuess()) {
                            done = true;
                            prevHit = true;
                        }
                    }
                }//end while loop

            } // end scope of else statement
        }
    }// end scope for carrier

    //if there are previous hits on the enemy battleship
    if ((hitsBattleshipHP != nullptr) && (!prevHit)) {
        count = 1;
        currPtr = hitsBattleshipHP;


        while (currPtr->next != nullptr) {
            currPtr = currPtr->next;
            count++;
        }

        //if the battleship has not been sunk
        if (count < 4) {

            //if there is more than one hit on enemy battleship
            if (count > 1) {

                done = false;
                //if ship is aligned vertically
                if (hitsBattleshipHP->hitCoord[0] == currPtr->hitCoord[0]) {

                    currPtr = hitsBattleshipHP;
                    searchPtr = hitsBattleshipHP;

                    //find hit with largest y coordinate
                    for (int j = 1; j < count; j++) {
                        searchPtr = searchPtr->next;
                        if (currPtr->hitCoord[1] < searchPtr->hitCoord[1]) {
                            currPtr = searchPtr;
                        }
                    }

                    //add 1 to the largest y coordinate and check if it is a valid guess
                    if ((currPtr->hitCoord[1] + 1) <= 9) {
                        getGuesses()->setNewGuess(currPtr->hitCoord[0], currPtr->hitCoord[1] + 1);
                        if (getGuesses()->checkGuess()) {
                            done = true;
                            prevHit = true;
                        }
                    }

                    if (!done) {

                        currPtr = hitsBattleshipHP;
                        searchPtr = hitsBattleshipHP;

                        //find hit with the smallest y coordinate
                        for (int j = 1; j < count; j++) {
                            searchPtr = searchPtr->next;
                            if (currPtr->hitCoord[1] > searchPtr->hitCoord[1]) {
                                currPtr = searchPtr;
                            }
                        }

                        //subtract 1 from smallest y coordinate and check if it is a valid guess
                        if ((currPtr->hitCoord[1] - 1) >= 0) {
                            getGuesses()->setNewGuess(currPtr->hitCoord[0], currPtr->hitCoord[1] - 1);
                            if (getGuesses()->checkGuess()) {
                                done = true;
                                prevHit = true;
                            }
                        }
                    }
                }// end scope of vertical case

                    //if ship is aligned horizontally
                else {

                    currPtr = hitsBattleshipHP;
                    searchPtr = hitsBattleshipHP;

                    //find hit with largest x coordinate
                    for (int j = 1; j < count; j++) {
                        searchPtr = searchPtr->next;
                        if (currPtr->hitCoord[0] < searchPtr->hitCoord[0]) {
                            currPtr = searchPtr;
                        }
                    }

                    //add 1 to the largest x coordinate and check if it is a valid guess
                    if ((currPtr->hitCoord[0] + 1) <= 9) {
                        getGuesses()->setNewGuess(currPtr->hitCoord[0] + 1, currPtr->hitCoord[1]);
                        if (getGuesses()->checkGuess()) {
                            done = true;
                            prevHit = true;
                        }
                    }

                    if (!done) {

                        currPtr = hitsBattleshipHP;
                        searchPtr = hitsBattleshipHP;

                        //find hit with the smallest x coordinate
                        for (int j = 1; j < count; j++) {
                            searchPtr = searchPtr->next;
                            if (currPtr->hitCoord[0] > searchPtr->hitCoord[0]) {
                                currPtr = searchPtr;
                            }
                        }

                        //subtract 1 from smallest x coordinate and check if it is a valid guess
                        if ((currPtr->hitCoord[0] - 1) >= 0) {
                            getGuesses()->setNewGuess(currPtr->hitCoord[0] - 1, currPtr->hitCoord[1]);
                            if (getGuesses()->checkGuess()) {
                                done = true;
                                prevHit = true;
                            }
                        }
                    }
                } // end case for enemy ship with horizontal orientation
            }//end case for enemy ship with more than one hit

                // else statement executes if there is only 1 hit on the battleship
            else {
                done = false;
                while (!done) {
                    randomNum = rand() % 4;

                    switch (randomNum) {
                        case 0: {
                            newGuess[0] = hitsBattleshipHP->hitCoord[0];
                            newGuess[1] = hitsBattleshipHP->hitCoord[1] + 1;
                            break;
                        }
                        case 1: {
                            newGuess[0] = hitsBattleshipHP->hitCoord[0] + 1;
                            newGuess[1] = hitsBattleshipHP->hitCoord[1];
                            break;
                        }
                        case 2: {
                            newGuess[0] = hitsBattleshipHP->hitCoord[0];
                            newGuess[1] = hitsBattleshipHP->hitCoord[1] - 1;
                            break;
                        }
                        case 3: {
                            newGuess[0] = hitsBattleshipHP->hitCoord[0] - 1;
                            newGuess[1] = hitsBattleshipHP->hitCoord[1];
                            break;
                        }
                    }// end switch

                    if ((newGuess[0] <= 9) && (newGuess[0] >= 0) && (newGuess[1] <= 9) && (newGuess[1] >= 0)) {

                        getGuesses()->setNewGuess(newGuess[0], newGuess[1]);

                        if (getGuesses()->checkGuess()) {
                            done = true;
                            prevHit = true;

                        }
                    }
                }//end while loop
            } // end scope of else statement
        }
    }//end scope for battleship

        //if there are previous hits on the enemy cruiser
        if ((hitsCruiserHP != nullptr) && (!prevHit)) {
            count = 1;
            currPtr = hitsCruiserHP;

            //count the number of hits
            while (currPtr->next != nullptr) {
                currPtr = currPtr->next;
                count++;
            }

            //if the enemy cruiser has not been sunk
            if (count < 3) {

                // if statement executes if there is more than one hit on the cruiser
                if (count > 1) {

                    done = false;
                    //if ship is aligned vertically
                    if (hitsCruiserHP->hitCoord[0] == currPtr->hitCoord[0]) {

                        currPtr = hitsCruiserHP;
                        searchPtr = hitsCruiserHP;

                        //find hit with largest y coordinate
                        for (int j = 1; j < count; j++) {
                            searchPtr = searchPtr->next;
                            if (currPtr->hitCoord[1] < searchPtr->hitCoord[1]) {
                                currPtr = searchPtr;
                            }
                        }

                        //add 1 to the largest y coordinate and check if it is a valid guess
                        if ((currPtr->hitCoord[1] + 1) <= 9) {
                            getGuesses()->setNewGuess(currPtr->hitCoord[0], currPtr->hitCoord[1] + 1);
                            if (getGuesses()->checkGuess()) {
                                done = true;
                                prevHit = true;
                            }
                        }

                        if (!done) {

                            currPtr = hitsCruiserHP;
                            searchPtr = hitsCruiserHP;

                            //find hit with the smallest y coordinate
                            for (int j = 1; j < count; j++) {
                                searchPtr = searchPtr->next;
                                if (currPtr->hitCoord[1] > searchPtr->hitCoord[1]) {
                                    currPtr = searchPtr;
                                }
                            }

                            //subtract 1 from smallest y coordinate and check if it is a valid guess
                            if ((currPtr->hitCoord[1] - 1) >= 0) {
                                getGuesses()->setNewGuess(currPtr->hitCoord[0], currPtr->hitCoord[1] - 1);
                                if (getGuesses()->checkGuess()) {
                                    done = true;
                                    prevHit = true;
                                }
                            }
                        }
                    }// end scope of vertical case

                        //if ship is aligned horizontally
                    else {

                        currPtr = hitsCruiserHP;
                        searchPtr = hitsCruiserHP;

                        //find hit with largest x coordinate
                        for (int j = 1; j < count; j++) {
                            searchPtr = searchPtr->next;
                            if (currPtr->hitCoord[0] < searchPtr->hitCoord[0]) {
                                currPtr = searchPtr;
                            }
                        }

                        //add 1 to the largest x coordinate and check if it is a valid guess
                        if ((currPtr->hitCoord[0] + 1) <= 9) {
                            getGuesses()->setNewGuess(currPtr->hitCoord[0] + 1, currPtr->hitCoord[1]);
                            if (getGuesses()->checkGuess()) {
                                done = true;
                                prevHit = true;
                            }
                        }

                        if (!done) {

                            currPtr = hitsCruiserHP;
                            searchPtr = hitsCruiserHP;

                            //find hit with the smallest x coordinate
                            for (int j = 1; j < count; j++) {
                                searchPtr = searchPtr->next;
                                if (currPtr->hitCoord[0] > searchPtr->hitCoord[0]) {
                                    currPtr = searchPtr;
                                }
                            }

                            //subtract 1 from smallest x coordinate and check if it is a valid guess
                            if ((currPtr->hitCoord[0] - 1) >= 0) {
                                getGuesses()->setNewGuess(currPtr->hitCoord[0] - 1, currPtr->hitCoord[1]);
                                if (getGuesses()->checkGuess()) {
                                    done = true;
                                    prevHit = true;
                                }
                            }
                        }
                    } // end case for enemy ship with horizontal orientation
                }//end case for enemy ship with more than one hit

                    // else statement executes if there is only 1 hit on the enemy cruiser
                else {
                    done = false;
                    while (!done) {
                        randomNum = rand() % 4;

                        switch (randomNum) {
                            case 0: {
                                newGuess[0] = hitsCruiserHP->hitCoord[0];
                                newGuess[1] = hitsCruiserHP->hitCoord[1] + 1;
                                break;
                            }
                            case 1: {
                                newGuess[0] = hitsCruiserHP->hitCoord[0] + 1;
                                newGuess[1] = hitsCruiserHP->hitCoord[1];
                                break;
                            }
                            case 2: {
                                newGuess[0] = hitsCruiserHP->hitCoord[0];
                                newGuess[1] = hitsCruiserHP->hitCoord[1] - 1;
                                break;
                            }
                            case 3: {
                                newGuess[0] = hitsCruiserHP->hitCoord[0] - 1;
                                newGuess[1] = hitsCruiserHP->hitCoord[1];
                                break;
                            }
                        }// end switch

                        if ((newGuess[0] <= 9) && (newGuess[0] >= 0) && (newGuess[1] <= 9) && (newGuess[1] >= 0)) {
                            getGuesses()->setNewGuess(newGuess[0], newGuess[1]);

                            if (getGuesses()->checkGuess()) {
                                done = true;
                                prevHit = true;
                            }
                        }
                    }//end while loop
                } // end scope of else statement
            }
        }// end scope for cruiser

        // if there are previous hits on the enemy submarine
        if ((hitsSubmarineHP != nullptr) && (!prevHit)) {
            count = 1;
            currPtr = hitsSubmarineHP;

            //count hits on enemy submarine
            while (currPtr->next != nullptr) {
                currPtr = currPtr->next;
                count++;
            }

            //if enemy submarine is not sunk
            if (count < 3) {

                // if statement executes if there is more than one hit on the submarine
                if (count > 1) {

                    done = false;
                    //if ship is aligned vertically
                    if (hitsSubmarineHP->hitCoord[0] == currPtr->hitCoord[0]) {

                        currPtr = hitsSubmarineHP;
                        searchPtr = hitsSubmarineHP;

                        //find hit with largest y coordinate
                        for (int j = 1; j < count; j++) {
                            searchPtr = searchPtr->next;
                            if (currPtr->hitCoord[1] < searchPtr->hitCoord[1]) {
                                currPtr = searchPtr;
                            }
                        }

                        //add 1 to the largest y coordinate and check if it is a valid guess
                        if ((currPtr->hitCoord[1] + 1) <= 9) {
                            getGuesses()->setNewGuess(currPtr->hitCoord[0], currPtr->hitCoord[1] + 1);
                            if (getGuesses()->checkGuess()) {
                                done = true;
                                prevHit = true;
                            }
                        }

                        if (!done) {

                            currPtr = hitsSubmarineHP;
                            searchPtr = hitsSubmarineHP;

                            //find hit with the smallest y coordinate
                            for (int j = 1; j < count; j++) {
                                searchPtr = searchPtr->next;
                                if (currPtr->hitCoord[1] > searchPtr->hitCoord[1]) {
                                    currPtr = searchPtr;
                                }
                            }

                            //subtract 1 from smallest y coordinate and check if it is a valid guess
                            if ((currPtr->hitCoord[1] - 1) >= 0) {
                                getGuesses()->setNewGuess(currPtr->hitCoord[0], currPtr->hitCoord[1] - 1);
                                if (getGuesses()->checkGuess()) {
                                    done = true;
                                    prevHit = true;
                                }
                            }
                        }
                    }// end scope of vertical case

                        //if ship is aligned horizontally
                    else {

                        currPtr = hitsSubmarineHP;
                        searchPtr = hitsSubmarineHP;

                        //find hit with largest x coordinate
                        for (int j = 1; j < count; j++) {
                            searchPtr = searchPtr->next;
                            if (currPtr->hitCoord[0] < searchPtr->hitCoord[0]) {
                                currPtr = searchPtr;
                            }
                        }

                        //add 1 to the largest x coordinate and check if it is a valid guess
                        if ((currPtr->hitCoord[0] + 1) <= 9) {
                            getGuesses()->setNewGuess(currPtr->hitCoord[0] + 1, currPtr->hitCoord[1]);
                            if (getGuesses()->checkGuess()) {
                                done = true;
                            }
                        }

                        if (!done) {

                            currPtr = hitsSubmarineHP;
                            searchPtr = hitsSubmarineHP;

                            //find hit with the smallest x coordinate
                            for (int j = 1; j < count; j++) {
                                searchPtr = searchPtr->next;
                                if (currPtr->hitCoord[0] > searchPtr->hitCoord[0]) {
                                    currPtr = searchPtr;
                                }
                            }

                            //subtract 1 from smallest y coordinate and check if it is a valid guess
                            if ((currPtr->hitCoord[0] - 1) >= 0) {
                                getGuesses()->setNewGuess(currPtr->hitCoord[0] - 1, currPtr->hitCoord[1]);
                                if (getGuesses()->checkGuess()) {
                                    done = true;
                                    prevHit = true;
                                }
                            }
                        }
                    } // end case for enemy ship with horizontal orientation
                }//end case for enemy ship with more than one hit

                    // else statement executes if there is only 1 hit on the submarine
                else {
                    done = false;
                    while (!done) {
                        randomNum = rand() % 4;

                        switch (randomNum) {
                            case 0: {
                                newGuess[0] = hitsSubmarineHP->hitCoord[0];
                                newGuess[1] = hitsSubmarineHP->hitCoord[1] + 1;
                                break;
                            }
                            case 1: {
                                newGuess[0] = hitsSubmarineHP->hitCoord[0] + 1;
                                newGuess[1] = hitsSubmarineHP->hitCoord[1];
                                break;
                            }
                            case 2: {
                                newGuess[0] = hitsSubmarineHP->hitCoord[0];
                                newGuess[1] = hitsSubmarineHP->hitCoord[1] - 1;
                                break;
                            }
                            case 3: {
                                newGuess[0] = hitsSubmarineHP->hitCoord[0] - 1;
                                newGuess[1] = hitsSubmarineHP->hitCoord[1];
                                break;
                            }
                        }// end switch

                        if ((newGuess[0] <= 9) && (newGuess[0] >= 0) && (newGuess[1] <= 9) && (newGuess[1] >= 0)) {


                            getGuesses()->setNewGuess(newGuess[0], newGuess[1]);

                            if (getGuesses()->checkGuess()) {
                                done = true;
                                prevHit = true;
                            }
                        }
                    }//end while loop

                } // end scope of else statement
            }
        }// end scope of submarine


        //if there are previous hits on the enemy destroyer
        if ((hitsDestroyerHP != nullptr) && (!prevHit)) {

            currPtr = hitsDestroyerHP;

            // if statement executes if there is one hit on the destroyer
            if (currPtr->next == nullptr) {
                done = false;
                while (!done) {
                    randomNum = rand() % 4;

                    switch (randomNum) {
                        case 0: {
                            newGuess[0] = hitsDestroyerHP->hitCoord[0];
                            newGuess[1] = hitsDestroyerHP->hitCoord[1] + 1;
                            break;
                        }
                        case 1: {
                            newGuess[0] = hitsDestroyerHP->hitCoord[0] + 1;
                            newGuess[1] = hitsDestroyerHP->hitCoord[1];
                            break;
                        }
                        case 2: {
                            newGuess[0] = hitsDestroyerHP->hitCoord[0];
                            newGuess[1] = hitsDestroyerHP->hitCoord[1] - 1;
                            break;
                        }
                        case 3: {
                            newGuess[0] = hitsDestroyerHP->hitCoord[0] - 1;
                            newGuess[1] = hitsDestroyerHP->hitCoord[1];
                            break;
                        }
                    }// end switch

                    if ((newGuess[0] <= 9) && (newGuess[0] >= 0) && (newGuess[1] <= 9) && (newGuess[1] >= 0)) {

                        getGuesses()->setNewGuess(newGuess[0], newGuess[1]);

                        if (getGuesses()->checkGuess()) {
                            done = true;
                            prevHit = true;
                        }
                    }
                }//end while loop

            } // end scope of else statement
        }

        if (!prevHit) {
            getGuesses()->computerGuess();
        }
}//end compGuessDecision
