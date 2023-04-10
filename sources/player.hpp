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

    public:
        Player() : _name("") {}

        Player(string);

        string getName();

        int stacksize();

        void setStacksize(int);

        int cardesTaken();

        void setCardesTaken(int);

        void deal_to_player(card &);  // insert a card into the player vec

        card & getCard();  // take a card from player vec
};