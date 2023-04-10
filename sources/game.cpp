//
// Created by shani on 26/03/2023.
//
// the shuffle taken from: https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector

#include "game.hpp"
#include "card.hpp"
#include <algorithm>  // for the shuffle of the deck
#include <random>  // for the shuffle of the deck
using namespace std;

/*
 * The constructor creates a deck, shuffle it and
 * divides the cards equally between the two players.
 */
Game::Game(Player & p1, Player & p2) : _p1(p1), _p2(p2){

    // create a deck
    vector<card> deck = *card::createDeck();

    // shuffle the deck
    auto g = std::default_random_engine {};
    shuffle(deck.begin(), deck.end(), g);

    // divides the deck equally between the two players
    for (size_t i = 0; i < deck.size(); ++i) {
        if (i%2 == 0)
            p1.deal_to_player(deck[i]);
        else
            p2.deal_to_player(deck[i]);
    }

    // updating
    this->cards_left = 26;  // number of cards that have left to each player
    this->_p1.setStacksize(26);
    this->_p2.setStacksize(26);

}

void Game::playTurn() {

    if(&this->_p1 == &this->_p2){
        throw runtime_error("player can't play alone!");
    }

    if(this->cards_left == 0){
        throw runtime_error("The game is already over!");
    }

    string winner;  // winner of the turn
    int cardsLeft;  // number of cards that have left to each player
    int cardValue1, cardValue2;

    do {  // until there is no a draw
        // take cards from players
        card c1 = _p1.getCard();
        card c2 = _p2.getCard();

        // the value of their cards in this turn
        cardValue1 = c1.getRank();
        cardValue2 = c2.getRank();

        winner = turn_winner(cardValue1, cardValue2);  // check who is the winner for this turn

        this->last_turn = _p1.getName() + " played " + c1.getRank_name() + " of " + c1.getSuit_name() + " " +
                          _p2.getName() + " played " + c2.getRank_name() + " of " + c2.getSuit_name() + ". ";

        if (winner == "p1") {
            int p1_cardsTaken = this->_p1.cardesTaken();  // the number of cards p1 won

            // updating
            this->_p1.setCardesTaken(p1_cardsTaken+1);

            this->last_turn += _p1.getName() + " won.\n";

        }

        if (winner == "p2") {
            int p2_cardsTaken = this->_p2.cardesTaken();  // the number of cards p2 won

            // updating: p2 won, p1 loss
            this->_p2.setCardesTaken(p2_cardsTaken+1);

            this->last_turn += _p2.getName() + " won.\n";
        }

        if (winner == "draw") {
            this->_p1.getCard();  // face-down card
            this->_p2.getCard(); // face-down card

            this->cards_left -= 2;  // to the identical rank card and to the face-down card

            // updating
            cardsLeft = this->cards_left;
            this->_p2.setStacksize(cardsLeft);
            this->_p1.setStacksize(cardsLeft);
            this->last_turn += " Draw.\n";
        }
    } while(winner != "draw");

    // updating
    cardsLeft = this->cards_left--;
    this->_p2.setStacksize(cardsLeft);
    this->_p1.setStacksize(cardsLeft);
    this->log += this->last_turn;
}

void Game::printLastTurn(){
    cout << this->last_turn << endl;
}

void Game::playAll(){
    do{
        playTurn();
    } while (this->cards_left > 0);
}

void Game::printWiner(){
    if (cards_left != 0){
        throw runtime_error("No winner. The players didn't finish the game!");
    }

    int p1_cards = this->_p1.cardesTaken();
    int p2_cards = this->_p2.cardesTaken();

    if (p1_cards > p2_cards){
        cout << _p1.getName() << endl;
    }
    else if(p2_cards > p1_cards){
        cout << _p2.getName() << endl;
    }
    else{
        cout << "It's a draw!" << endl;
    }
}

void Game::printLog(){
    cout << this->log << endl;
}

void Game::printStats() {
    cout << "states" << endl;
}


string Game::turn_winner(int p1_cardValue, int p2_cardValue){
    if (p1_cardValue > p2_cardValue) {
        if (p1_cardValue == card::As && p2_cardValue == card::two) { return "p2"; } // by the rules 2 wins As -> p2 is the winner
        return "p1";
    }

    else {
        if (p2_cardValue > p1_cardValue) {
            if (p2_cardValue == card::As && p1_cardValue == card::two) { return "p1"; }
            return "p2";
        }

        return "draw";
    }
}