//
// Created by shani on 26/03/2023.
//

#ifndef CARDWAR_A_CARD_H
#define CARDWAR_A_CARD_H
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class card {
    public:
        // list of all the ranks and suits which familiar with the game cards
        enum Rank {two = 2, three, four, five, six, seven, eight, nine, ten, jack, queen, king, As};
        enum Suit {diamonds, clubs, hearts, spades};

        card(int rank, int suit);

        int getRank() const;

        std::string getRank_name() const;

        std::string getSuit_name() const;

        static vector<card>* createDeck();  // creat a deck of cards with 52 cards as usual (without jokers)

    private:
        int _rank;
        int _suit;
};

#endif //CARDWAR_A_CARD_H
