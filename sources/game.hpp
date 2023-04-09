//
// Created by shani on 26/03/2023.
//

#ifndef CARDWAR_A_GAME_H
#define CARDWAR_A_GAME_H
#include "player.hpp"

namespace ariel {}
    class Game {
    private:
        Player _p1;
        Player _p2;

    public:
        Game() {
            this->_p1 = Player();
            this->_p2 = Player();
        }

        Game(Player p1, Player p2){
            this->_p1 = p1;
            this->_p2 = p2;
        }

        void playTurn();

        string printLastTurn();

        void playAll();

        string printWiner();

        string printLog();

        string printStats();
    };


#endif //CARDWAR_A_GAME_H
