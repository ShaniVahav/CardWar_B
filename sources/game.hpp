//
// Created by shani on 26/03/2023.
//

#ifndef CARDWAR_A_GAME_H
#define CARDWAR_A_GAME_H
#include "player.hpp"
#include <string>

namespace ariel {}
    class Game {
    private:
        Player & _p1;
        Player & _p2;
        string last_turn = "";
        string log = "";
        int cards_left = 0;

    public:
        Game(Player & p1, Player & p2);

        void playTurn();

        void printLastTurn();

        void playAll();

        void printWiner();

        void printLog();

        void printStats();

        string turn_winner(int, int);  // the winner of a turn ("p1" or "p2" or "draw")
    };


#endif //CARDWAR_A_GAME_H
