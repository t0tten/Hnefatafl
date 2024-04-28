//
//  piece.cpp
//  Hnefatafl
//
//  Created by Rasmus Schenström on 2024-04-27.
//

#include "piece.hpp"
#include <iostream>
#include <string>

Piece::Piece(PieceType pieceType, std::string color, bool isDefender)
{
    this->pieceType = pieceType;
    this->color = color;
    this->defender = isDefender;
    
    std::string message = "Creating ";
    switch (this->pieceType)
    {
        case PieceType::WARRIOR:
            message += "WARRIOR (";
            break;
        case PieceType::KING:
            message += "KING (";
            break;
        default:
            break;
    }
     message += this->getSign() + ") with color " + color;
     this->log->debug(message);
}

Piece::~Piece() {}

std::string Piece::getSign()
{
    switch (this->pieceType)
    {
        case PieceType::WARRIOR:
            return "!";
        case PieceType::KING:
            return "@";
        default:
            break;
    }
}

void Piece::setCoord(short x, short y)
{
    this->x = x;
    this->y = y;
}

short Piece::getX()
{
    return this->x;
}

short Piece::getY()
{
    return this->y;
}

std::string Piece::getColor()
{
    return this->color;
}

bool Piece::isDefender()
{
    return this->defender;
}

bool Piece::isKing()
{
    return (this->pieceType == PieceType::KING);
}
