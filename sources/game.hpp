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
        string last_turn;
        string log;
        int turnsLeft = 0;
        int draw_rate = 0;


    public:
        Game(Player & p1, Player & p2);

        void playTurn();

        void printLastTurn() {cout << this->last_turn << endl;}

        void playAll(){ while (this->turnsLeft > 0) { playTurn(); } }

        void printWiner();

        void printLog() {cout << this->log << endl;}

        void printStats();

        private: Player & turn_winner(int, int);  // return the winner of the turn
    };


#endif //CARDWAR_A_GAME_H
