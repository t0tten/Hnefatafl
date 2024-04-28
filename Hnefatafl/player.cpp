//
//  player.cpp
//  Hnefatafl
//
//  Created by Rasmus Schenström on 2024-04-27.
//

#include "player.hpp"
#include <iostream>

#define BLUE_BOLD "\033[1;94m"
//#define BLUE_BOLD ""

Player::Player(short sizeWarriors) : Player(sizeWarriors, std::string(BLUE_BOLD), false) {}
Player::Player(short sizeWarriors, std::string color, bool isDefender)
{
    this->log->debug("Player constructor");
    this->sizeWarriors = this->warriorsLeft = sizeWarriors;
    this->warriors = new Piece*[sizeWarriors];
    for (int i = 0; i < this->sizeWarriors; i++) {
        this->warriors[i] = new Piece(Piece::PieceType::WARRIOR, color, isDefender);
    }
}

Player::~Player()
{
    for (int i = 0; i < this->sizeWarriors - 1; i++) {
        delete this->warriors[i];
    }
    delete this->warriors;
}

Piece** Player::getWarriors()
{
    return this->warriors;
}

short Player::getSize()
{
    return this->warriorsLeft;
}

std::string Player::getColor()
{
    return std::string(BLUE_BOLD);
}

std::string Player::getName()
{
    return "ATTACKER";
}

void Player::placePieces()
{
    this->log->debug("Place pieces");
    
    // top
    this->warriors[0]->setCoord(0,3);
    this->warriors[1]->setCoord(0,4);
    this->warriors[2]->setCoord(0,5);
    this->warriors[3]->setCoord(0,6);
    this->warriors[4]->setCoord(0,7);
    this->warriors[5]->setCoord(1,5);
    
    // right
    this->warriors[6]->setCoord(3,10);
    this->warriors[7]->setCoord(4,10);
    this->warriors[8]->setCoord(5,10);
    this->warriors[9]->setCoord(6,10);
    this->warriors[10]->setCoord(7,10);
    this->warriors[11]->setCoord(5,9);
    
    // bottom
    this->warriors[12]->setCoord(10,3);
    this->warriors[13]->setCoord(10,4);
    this->warriors[14]->setCoord(10,5);
    this->warriors[15]->setCoord(10,6);
    this->warriors[16]->setCoord(10,7);
    this->warriors[17]->setCoord(9,5);
    
    // left
    this->warriors[18]->setCoord(3,0);
    this->warriors[19]->setCoord(4,0);
    this->warriors[20]->setCoord(5,0);
    this->warriors[21]->setCoord(6,0);
    this->warriors[22]->setCoord(7,0);
    this->warriors[23]->setCoord(5,1);
}
