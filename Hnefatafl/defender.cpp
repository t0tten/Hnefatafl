//
//  defender.cpp
//  Hnefatafl
//
//  Created by Rasmus Schenström on 2024-04-27.
//

#include "defender.hpp"
#include <iostream>

#define GREEN_BOLD "\033[1;32m"
//#define GREEN_BOLD ""

Defender::Defender(short sizeWarriors) : Player(sizeWarriors, std::string(GREEN_BOLD), true)
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
    
    this->warriors[0]->setCoord(3,5);
    
    this->warriors[1]->setCoord(4,4);
    this->warriors[2]->setCoord(4,5);
    this->warriors[3]->setCoord(4,6);
    
    this->warriors[4]->setCoord(5,3);
    this->warriors[5]->setCoord(5,4);
    this->warriors[6]->setCoord(5,6);
    this->warriors[7]->setCoord(5,7);
    
    this->warriors[8]->setCoord(6,4);
    this->warriors[9]->setCoord(6,5);
    this->warriors[10]->setCoord(6,6);
    
    this->warriors[11]->setCoord(7,5);
    
    this->king->setCoord(5, 5);
}

Piece* Defender::getKing()
{
    return this->king;
}
