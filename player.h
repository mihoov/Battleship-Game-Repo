//
// Created by hoove on 11/29/2019.
//

#include "guesses.h"
#include "shipPlacement.h"
#include <random>
#include <cstdlib>
#include <ctime>

#ifndef FINAL_PROJECT_PLAYER_H
#define FINAL_PROJECT_PLAYER_H

#endif //FINAL_PROJECT_PLAYER_H

class Player {
private:
    bool humanPlayer;
    bool winCondition;
    Guesses playerGuesses;
    ShipPlacement playerShipPlacement;


    //for computer player AI to keep track of hits on user's ships
    struct compHit {
        int hitCoord[2];
        compHit* next;
    };

    compHit* hitsCarrierHP;
    compHit* hitsBattleshipHP;
    compHit* hitsCruiserHP;
    compHit* hitsSubmarineHP;
    compHit* hitsDestroyerHP;

public:

    Player(bool humPlay);

    Guesses* getGuesses();
    ShipPlacement* getShipPlacement();

    bool getWinCondition();
    void setWinCodntion(Player &opponent);

    void takeTurn(Player &opponentPlayer) throw (QuitGame);
    void compGuessDecision();
    void checkHit(Player &opponentShips);


};