//
// Created by shani on 26/03/2023.
//
#pragma once

class Player{
    private:
        string _name;

    public:
    Player() {
        this->_name = "";
    };

    Player(std::string name);

        string getName();
        void setName(string newName);
        int stacksize();
        int cardesTaken();
};