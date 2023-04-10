//
// Created by shani on 10/04/2023.
//

#include "card.hpp"
using namespace std;

card::card(int rank, int suit) {
    this->_rank = rank;
    this->_suit = suit;
}

int card::getRank() {
    return this->_rank;
}

string card::getRank_name() {
    int rank = this->_rank;
    switch (rank) {
        case 11: return "Jack";
        case 12: return "Queen";
        case 13: return "King";
        case 14: return "As";
        default: return to_string(rank);
    }
}

string card::getSuit_name() {
    int suit = this->_suit;
    cout << suit << endl;
    switch (suit) {
        case 0: return "Diamonds";
        case 1: return "Clubs";
        case 2: return "Hearts";
        case 3: return "Spades";
        default: throw std::runtime_error("ERR: suit not exist. suit = " + to_string(suit));
    }
}

vector <card>* card::createDeck() {
    vector<card>* deck = new vector<card>;

    for(int rank = two; rank <= As; rank++){
        for (int suit = diamonds; suit <= spades; suit++) {
            deck->push_back(card(rank, suit));
        }
    }

    return deck;
}