//
//  defender.cpp
//  Hnefatafl
//
//  Created by Rasmus Schenström on 2024-04-27.
//

#include <iostream>

#include "constants.hpp"
#include "defender.hpp"
#include <iostream>

Defender::Defender(short width, short height) : Player(Constants::DEFENDER_COLOR, true, width, height)
{
    this->log->debug("Defender constructor");
    this->king = new Piece(Piece::PieceType::KING, Constants::DEFENDER_COLOR, true);
}

Defender::~Defender()
{
    delete this->king;
}

std::string Defender::getColor()
{
    return Constants::DEFENDER_COLOR;
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
    
    this->king->setCoord(halfWidth, halfHeight);
    
    this->warriors[0]->setCoord(halfWidth - 1, halfHeight);
    this->warriors[1]->setCoord(halfWidth, halfHeight - 1);
    this->warriors[2]->setCoord(halfWidth, halfHeight + 1);
    this->warriors[3]->setCoord(halfWidth + 1, halfHeight);
    
    if (this->width <= 11)
    {
        this->warriors[4]->setCoord(halfWidth - 2, halfHeight);
        this->warriors[5]->setCoord(halfWidth, halfHeight - 2);
        this->warriors[6]->setCoord(halfWidth, halfHeight + 2);
        this->warriors[7]->setCoord(halfWidth + 2, halfHeight);
    }
    
    if (this->width == 11)
    {
        this->warriors[8]->setCoord(halfWidth - 1, halfHeight + 1);
        this->warriors[9]->setCoord(halfWidth - 1, halfHeight - 1);
        this->warriors[10]->setCoord(halfWidth + 1, halfHeight + 1);
        this->warriors[11]->setCoord(halfWidth + 1, halfHeight - 1);
    }
    
    if (this->width == 19)
    {
        this->warriors[4]->setCoord(halfWidth - 3, halfHeight);
        this->warriors[5]->setCoord(halfWidth, halfHeight - 3);
        this->warriors[6]->setCoord(halfWidth, halfHeight + 3);
        this->warriors[7]->setCoord(halfWidth + 3, halfHeight);
        
        this->warriors[8]->setCoord(halfWidth - 2 ,halfHeight - 1);
        this->warriors[9]->setCoord(halfWidth - 2, halfHeight + 1);
        this->warriors[10]->setCoord(halfWidth - 1, halfHeight - 2);
        this->warriors[11]->setCoord(halfWidth + 1, halfHeight - 2);
        
        this->warriors[12]->setCoord(halfWidth + 2 ,halfHeight - 1);
        this->warriors[13]->setCoord(halfWidth + 2, halfHeight + 1);
        this->warriors[14]->setCoord(halfWidth - 1, halfHeight + 2);
        this->warriors[15]->setCoord(halfWidth + 1, halfHeight + 2);
        
        this->warriors[16]->setCoord(halfWidth - 5 ,halfHeight - 1);
        this->warriors[17]->setCoord(halfWidth - 5, halfHeight + 1);
        this->warriors[18]->setCoord(halfWidth + 5, halfHeight - 1);
        this->warriors[19]->setCoord(halfWidth + 5, halfHeight + 1);
        
        this->warriors[20]->setCoord(halfWidth - 1 ,halfHeight - 5);
        this->warriors[21]->setCoord(halfWidth + 1, halfHeight - 5);
        this->warriors[22]->setCoord(halfWidth - 1, halfHeight + 5);
        this->warriors[23]->setCoord(halfWidth + 1, halfHeight + 5);
    }
}

Piece* Defender::getKing()
{
    return this->king;
}
