//
//  configurations.cpp
//  Hnefatafl
//
//  Created by Rasmus Schenström on 2024-04-30.
//

#include "configurations.hpp"

Configurations::Configurations()
{
    this->playerTurn = this->me = 0;
    this->width = 11;
    this->height = 11;
    this->size = "medium";
    this->isNetworkMode = false;
    this->port = 27925;
}

short Configurations::getPlayerTurn()
{
    return this->playerTurn % 2;
}

short Configurations::getMe()
{
    return this->me;
}

short Configurations::getWidth()
{
    return this->width;
}

short Configurations::getHeight()
{
    return this->height;
}

std::string Configurations::getSizeText()
{
    return this->size;
}

int Configurations::getPort()
{
    return this->port;
}

bool Configurations::getIsNetworkEnabled()
{
    return this->isNetworkMode;
}

void Configurations::switchStartPlayer()
{
    this->playerTurn++;
}

void Configurations::setPlayerTurn(short playerTurn)
{
    this->playerTurn = playerTurn;
}

void Configurations::setMe(short playerTurn)
{
    this->me = playerTurn;
}

void Configurations::setWidth(short width)
{
    this->width = width;
}

void Configurations::setHeight(short height)
{
    this->height = height;
}

void Configurations::setSizeText(std::string size)
{
    this->size = size;
}

void Configurations::setPort(int port)
{
    this->port = port;
}

void Configurations::setNetworkEnabled()
{
    this->isNetworkMode = true;
}
