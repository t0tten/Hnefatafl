//
//  player.cpp
//  Hnefatafl
//
//  Created by Rasmus Schenström on 2024-04-27.
//

#include <iostream>

#include "constants.hpp"
#include "player.hpp"

Player::Player(short width, short height) : Player(Constants::ATTACKER_COLOR, false, width, height) {}
Player::Player(std::string color, bool isDefender, short width, short height)
{
    this->log->debug("Player constructor");
    this->width = width;
    this->height = height;

    if (isDefender)
    {
        if (width == 9) sizeWarriors = 8;
        else if (width == 11) sizeWarriors = 12;
        else if (width == 19) sizeWarriors = 24;
    }
    else
    {
        if (width == 9) sizeWarriors = 4*4;
        else if (width == 11) sizeWarriors = 6*4;
        else if (width == 19) sizeWarriors = 48;
    }
    
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
    
    if (this->width <= 11)
    {
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
        if (this->width == 11)
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
    
    if (this->width == 19)
    {
        this->warriors[0]->setCoord(0, halfHeight - 4);
        this->warriors[1]->setCoord(0, halfHeight - 7);
        this->warriors[2]->setCoord(0, halfHeight + 4);
        this->warriors[3]->setCoord(0, halfHeight + 7);
        
        this->warriors[4]->setCoord(halfWidth - 4, 0);
        this->warriors[5]->setCoord(halfWidth - 7, 0);
        this->warriors[6]->setCoord(halfWidth + 4, 0);
        this->warriors[7]->setCoord(halfWidth + 7, 0);
        
        this->warriors[8]->setCoord(halfWidth - 4, this->height - 1);
        this->warriors[9]->setCoord(halfWidth - 7, this->height - 1);
        this->warriors[10]->setCoord(halfWidth + 4, this->height - 1);
        this->warriors[11]->setCoord(halfWidth + 7, this->height - 1);
        
        this->warriors[12]->setCoord(this->width - 1, halfHeight - 4);
        this->warriors[13]->setCoord(this->width - 1, halfHeight - 7);
        this->warriors[14]->setCoord(this->width - 1, halfHeight + 4);
        this->warriors[15]->setCoord(this->width - 1, halfHeight + 7);
        
        this->warriors[16]->setCoord(2, halfHeight - 4);
        this->warriors[17]->setCoord(2, halfHeight + 4);
        this->warriors[18]->setCoord(halfWidth - 4, 2);
        this->warriors[19]->setCoord(halfWidth + 4, 2);
        this->warriors[20]->setCoord(this->width - 3, halfHeight - 4);
        this->warriors[21]->setCoord(this->width - 3, halfHeight + 4);
        this->warriors[22]->setCoord(halfWidth - 4, this->height - 3);
        this->warriors[23]->setCoord(halfWidth + 4, this->height - 3);
        
        // straight
        this->warriors[24]->setCoord(halfWidth - 2, halfHeight - 6);
        this->warriors[25]->setCoord(halfWidth, halfHeight - 6);
        this->warriors[26]->setCoord(halfWidth + 2, halfHeight - 6);
        
        this->warriors[27]->setCoord(halfWidth - 2, halfHeight + 6);
        this->warriors[28]->setCoord(halfWidth, halfHeight + 6);
        this->warriors[29]->setCoord(halfWidth + 2, halfHeight + 6);
        
        this->warriors[30]->setCoord(halfWidth - 6, halfHeight - 2);
        this->warriors[31]->setCoord(halfWidth - 6, halfHeight);
        this->warriors[32]->setCoord(halfWidth - 6, halfHeight + 2);
        
        this->warriors[33]->setCoord(halfWidth + 6, halfHeight - 2);
        this->warriors[34]->setCoord(halfWidth + 6, halfHeight);
        this->warriors[35]->setCoord(halfWidth + 6, halfHeight + 2);
        
        // diagonal
        this->warriors[36]->setCoord(halfWidth - 5, halfHeight + 3);
        this->warriors[37]->setCoord(halfWidth - 4, halfHeight + 4);
        this->warriors[38]->setCoord(halfWidth - 3, halfHeight + 5);
        
        this->warriors[39]->setCoord(halfWidth + 5, halfHeight - 3);
        this->warriors[40]->setCoord(halfWidth + 4, halfHeight - 4);
        this->warriors[41]->setCoord(halfWidth + 3, halfHeight - 5);
        
        this->warriors[42]->setCoord(halfWidth + 5, halfHeight + 3);
        this->warriors[43]->setCoord(halfWidth + 4, halfHeight + 4);
        this->warriors[44]->setCoord(halfWidth + 3, halfHeight + 5);
        
        this->warriors[45]->setCoord(halfWidth - 5, halfHeight - 3);
        this->warriors[46]->setCoord(halfWidth - 4, halfHeight - 4);
        this->warriors[47]->setCoord(halfWidth - 3, halfHeight - 5);
    }
}
