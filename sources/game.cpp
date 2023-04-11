//
// Created by shani on 26/03/2023.
//

#include "game.hpp"
#include "card.hpp"
#include <algorithm>  // for the shuffle of the deck
#include <random>  // for the shuffle of the deck
#include <chrono>
using namespace std;

/*
 * The constructor creates a deck, shuffle it and
 * divides the cards equally between the two players.
 */
Game::Game(Player & p1, Player & p2) : _p1(p1), _p2(p2){

    // create a deck
    vector<card> deck = *card::createDeck();

    // shuffle the deck
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine rand(seed);  // rand number based on time
    shuffle(deck.begin(), deck.end(), rand);


    // divides the deck equally between the two players
    for (size_t i = 0; i < deck.size(); ++i) {
        if (i%2 == 0)
            p1.deal_to_player(deck[i]);
        else
            p2.deal_to_player(deck[i]);
    }

    // updating
    this->turnsLeft = 26;
    this->_p1.setStacksize(26);
    this->_p2.setStacksize(26);

}

void Game::playTurn() {

    if(&this->_p1 == &this->_p2){
        throw runtime_error("player can't play alone!");
    }

    int winner_cardsTaken = 2; // in a turn
    int cardValue1, cardValue2;
    bool is_draw;

    this->last_turn = "";  // reset

    do {  // until there is no draw

        if(this->turnsLeft <= 0){
            throw runtime_error("The game is already over!");
        }

        // take cards from players
        card c1 = _p1.getCard();
        card c2 = _p2.getCard();

        // the value of their cards in this turn
        cardValue1 = c1.getRank();
        cardValue2 = c2.getRank();


        this->last_turn += _p1.getName() + " played " + c1.getRank_name() + " of " + c1.getSuit_name() + " " +
                          _p2.getName() + " played " + c2.getRank_name() + " of " + c2.getSuit_name() + ". ";


        try {

            // check who is the winner for this turn
            Player & winner = turn_winner(cardValue1, cardValue2);

            // it's not a draw
            is_draw = false;

            // updating winner
            winner.setCardesTaken(winner.cardesTaken()+winner_cardsTaken);
            winner.increase_win_rate();
            this->last_turn += winner.getName() + " won.\n";

            // updating stacks
            this->_p2.setStacksize(this->_p2.stacksize()-winner_cardsTaken/2);
            this->_p1.setStacksize(this->_p1.stacksize()-winner_cardsTaken/2);

            this->turnsLeft -= 1;
            winner_cardsTaken = 2;  // reset
        }
        catch(exception& e) {
            // it's a draw
            is_draw = true;
            this->draw_rate++;

            this->_p1.getCard();  // face-down card
            this->_p2.getCard(); // face-down card

            // updating
            this->turnsLeft -= 2;  // to the identical rank card and to the face-down card

            winner_cardsTaken += 4;

            this->last_turn += " Draw.\n";
        }

    } while(is_draw);

    this->log += this->last_turn;
}

void Game::printWiner(){
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


void Game::printStats() {
    Player & p1 = this->_p1;
    Player & p2 = this->_p2;

    cout << p1.getName() << endl
         << "Finish with " << p1.cardesTaken() << " cards." << endl
         << "Win rate: " << p1.get_win_rate() << endl << endl

         << p2.getName() << endl
         << "Finish with " << p2.cardesTaken() << " cards." << endl
         << "Win rate: " << p2.get_win_rate() << endl << endl

         << "number of draws: " << this->draw_rate << endl;
}


Player & Game::turn_winner(int p1_cardValue, int p2_cardValue){
    if (p1_cardValue > p2_cardValue) {
        if (p1_cardValue == card::As && p2_cardValue == card::two)
        {
            return this->_p2; // by the rules 2 wins As -> p2 is the winner
        }
        return this->_p1;
    }

    else {
        if (p2_cardValue > p1_cardValue)
        {
            if (p2_cardValue == card::As && p1_cardValue == card::two)
            {
                return this->_p1;
            }
            return this->_p2;
        }

        throw runtime_error("draw");
    }
}