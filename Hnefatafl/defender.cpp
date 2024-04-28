//
//  defender.cpp
//  Hnefatafl
//
//  Created by Rasmus Schenström on 2024-04-27.
//

#include "defender.hpp"
#include <iostream>

#define GREEN_BOLD "\033[1;32m"

Defender::Defender(short sizeWarriors, short width, short height) : Player(sizeWarriors, std::string(GREEN_BOLD), true, width, height)
{
    this->log->debug("Defender constructor");
    this->king = new Piece(Piece::PieceType::KING, std::string(GREEN_BOLD), true);
}

Defender::~Defender()
{
    delete this->king;
}

std::string Defender::getColor()
{
    return std::string(GREEN_BOLD);
}

std::string Defender::getName()
{
    return "DEFENDER";
}

void Defender::placePieces()
{
    this->log->debug("Place pieces Defender");
    short halfWidth = this->width/2;
    short halfHeight = this->height/2;
    
    this->warriors[0]->setCoord(halfWidth - 2, halfHeight);
    this->warriors[1]->setCoord(halfWidth - 1 ,halfHeight);
    this->warriors[2]->setCoord(halfWidth, halfHeight - 2);
    this->warriors[3]->setCoord(halfWidth, halfHeight - 1);

    this->king->setCoord(halfWidth, halfHeight);

    this->warriors[4]->setCoord(halfWidth, halfHeight + 1);
    this->warriors[5]->setCoord(halfWidth, halfHeight + 2);
    this->warriors[6]->setCoord(halfWidth + 1, halfHeight);
    this->warriors[7]->setCoord(halfWidth + 2, halfHeight);
    
    //Extras
    if (this->width > 10)
    {
        this->warriors[8]->setCoord(halfWidth - 1, halfHeight + 1);
        this->warriors[9]->setCoord(halfWidth - 1, halfHeight - 1);
        this->warriors[10]->setCoord(halfWidth + 1, halfHeight + 1);
        this->warriors[11]->setCoord(halfWidth + 1, halfHeight - 1);
    }
}

Piece* Defender::getKing()
{
    return this->king;
}
