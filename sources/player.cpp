//
// Created by shani on 26/03/2023.
//

#include "player.hpp"
using namespace std;

void Player::deal_to_player(card & c){
    this->cards.push_back(c);
}

card & Player::getCard(){
    card* c = &this->cards.back();
    this->cards.pop_back();
    return *c;
}