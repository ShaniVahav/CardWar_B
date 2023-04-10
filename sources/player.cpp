//
// Created by shani on 26/03/2023.
//

#include "player.hpp"
using namespace std;

Player::Player(string name) {
    this->_name = name;
}
string Player::getName(){
    return this->_name;
}
int Player::stacksize(){
    return this->stack_size;
}

void Player::setStacksize(int num) {
    this->stack_size = num;
}

int Player::cardesTaken() {
    return this->cards_taken;
}

void Player::setCardesTaken(int num) {
    this->cards_taken = num;
}

void Player::deal_to_player(card & c){
    this->cards.push_back(c);
}

card & Player::getCard(){
    card* c = &this->cards.back();
    this->cards.pop_back();
    return *c;
}