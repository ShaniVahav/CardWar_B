//
// Created by shani on 26/03/2023.
//
#pragma once
#include <string>
#include "card.hpp"
using namespace std;


class Player{
    private:
        string _name;
        vector<card> cards;
        int stack_size = 0;
        int cards_taken = 0;
        int win_rate = 0;

    public:
        Player(string name = "") : _name(std::move(name)) {}

        string getName() const {return this->_name;}

        int stacksize() const {return this->stack_size;}

        void setStacksize(int  num) {this->stack_size = num;}

        int cardesTaken() const {return this->cards_taken;}

        void setCardesTaken(int num) {this->cards_taken = num;}

        void increase_win_rate() {this->win_rate++;}

        int get_win_rate() const {return this->win_rate;}

        void deal_to_player(card &);  // insert a card into the player vec

        card & getCard();  // take a card from player vec
};