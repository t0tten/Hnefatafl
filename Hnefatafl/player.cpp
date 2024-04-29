//
//  player.cpp
//  Hnefatafl
//
//  Created by Rasmus Schenström on 2024-04-27.
//

#include <iostream>

#include "constants.hpp"
#include "player.hpp"

Player::Player(short sizeWarriors, short width, short height) : Player(sizeWarriors, Constants::ATTACKER_COLOR, false, width, height) {}
Player::Player(short sizeWarriors, std::string color, bool isDefender, short width, short height)
{
    this->log->debug("Player constructor");
    this->width = width;
    this->height = height;
    if (this->width <= 10) sizeWarriors = (isDefender) ? 8 : 16;
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
    return Constants::ATTACKER_COLOR;
}

std::string Player::getName()
{
    return "ATTACKER";
}

void Player::placePieces()
{
    this->log->debug("Place pieces");
    
    short halfWidth = this->width/2;
    short halfHeight = this->height/2;
    
    // left
    this->warriors[0]->setCoord(0, halfHeight - 1);
    this->warriors[1]->setCoord(0, halfHeight);
    this->warriors[2]->setCoord(0, halfHeight + 1);
    this->warriors[3]->setCoord(1, halfHeight);
    
    // bottom
    this->warriors[4]->setCoord(halfWidth - 1, this->height - 1);
    this->warriors[5]->setCoord(halfWidth, this->height - 1);
    this->warriors[6]->setCoord(halfWidth + 1, this->height - 1);
    this->warriors[7]->setCoord(halfWidth, this->height - 2);
    
    // right
    this->warriors[8]->setCoord(this->width - 1, halfHeight - 1);
    this->warriors[9]->setCoord(this->width - 1, halfHeight);
    this->warriors[10]->setCoord(this->width - 1, halfHeight + 1);
    this->warriors[11]->setCoord(this->width - 2, halfHeight);
    
    // top
    this->warriors[12]->setCoord(halfWidth - 1, 0);
    this->warriors[13]->setCoord(halfWidth, 0);
    this->warriors[14]->setCoord(halfWidth + 1, 0);
    this->warriors[15]->setCoord(halfWidth, 1);
    
    //Extras
    if (this->width > 10)
    {
        this->warriors[16]->setCoord(0, halfHeight - 2);
        this->warriors[17]->setCoord(0, halfHeight + 2);
        this->warriors[18]->setCoord(halfWidth - 2, this->height - 1);
        this->warriors[19]->setCoord(halfWidth + 2, this->height - 1);
        this->warriors[20]->setCoord(this->width - 1, halfHeight - 2);
        this->warriors[21]->setCoord(this->width - 1, halfHeight + 2);
        this->warriors[22]->setCoord(halfWidth - 2, 0);
        this->warriors[23]->setCoord( halfWidth + 2, 0);
    }
    
}
