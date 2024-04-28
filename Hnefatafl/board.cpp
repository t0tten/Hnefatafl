//
//  board.cpp
//  Hnefatafl
//
//  Created by Rasmus Schenström on 2024-04-26.
//

#include "board.hpp"
#include <iostream>

#define GREEN_BOLD      "\033[1;32m"
#define BLUE_BOLD       "\033[1;94m"
#define CYAN_REGULAR    "\033[0;96m"
#define RESET_REGULAR   "\033[0m"

//#define CYAN_REGULAR    ""
//#define RESET_REGULAR   ""


Board::Board(short width, short height)
{
    this->log->info("Board constructor");
    this->width = width;
    this->height = height;

    this->log->debug("Initializing board");
    this->board = new Piece**[this->width];
    for (int x = 0; x < this->width; x++)
    {
        this->board[x] = new Piece*[this->height];
        for (int y = 0; y < this->height; y++)
        {
            this->board[x][y] = nullptr;
        }
    }
}

Board::~Board()
{
    for (int x = 0; x < this->width; x++)
    {
        for (int y = 0; y < this->height; y++)
        {
            if (this->board[x][y] != nullptr)
            {
                delete this->board[x][y];
            }
        }
        delete this->board[x];
    }
    delete this->board;
}

void Board::printBoardHeader()
{
    short numLoops = (short)this->width / 10;
    for (int j = 0; j <= numLoops; j++)
    {
        std::cout << "   ";
        for (int x = 0; x < this->width; x++)
        {
            if (numLoops > 0 && j == 0)
            {
                std::string numStr = " ";
                if (x > 9) {
                    short tmpX = (short) x / 10;
                    numStr = std::to_string(tmpX);
                }
                std::cout << " " << numStr;
            }
            else
            {
                short tmpX = (x < 10) ? x : x - 10;
                std::cout << " " << tmpX;
            }
        }
        std::cout << std::endl;
    }
}

void Board::printBoard(short attackerCaptured, short defenderCaptured)
{
    this->printBoardHeader();
    for (int y = 0; y < this->height; y++)
    {
        std::string padding = " ";
        if (y < 10) {
            padding += " ";
        }
        padding += std::to_string(y) + "|";
        std::cout << padding;
        
        for (int x = 0; x < this->width; x++)
        {
            Piece* piece = this->board[x][y];
            if (piece != nullptr)
            {
                std::cout << this->board[x][y]->getColor() << this->board[x][y]->getSign() << std::string(RESET_REGULAR);
            } else {
                if (this->isKingsSquare(x, y)) {
                    std::cout << std::string(CYAN_REGULAR) + "X" + std::string(RESET_REGULAR);
                } else {
                    std::cout << "_";
                }
            }
            std::cout << "|";
        }
        if (y == 0)
        {
            std::cout << " ATTACKER";
        }
        if (y == 1)
        {
            std::cout << " [" << std::string(BLUE_BOLD);
            for (int i = 0; i < attackerCaptured; i++)
            {
                std::cout << "!";
            }
            std::cout << std::string(RESET_REGULAR) << "]";
        }
        if (y == 3)
        {
            std::cout << " DEFENDER";
        }
        if (y == 4)
        {
            std::cout << " [" << std::string(GREEN_BOLD);
            for (int i = 0; i < defenderCaptured; i++)
            {
                std::cout << "!";
            }
            std::cout << std::string(RESET_REGULAR) << "]";
        }
        std::cout << std::endl;
        
        
    }
}

bool Board::isKingsSquare(short x, short y)
{
    short midX = this->width / 2;
    short midY = this->height /2;
    
    if ((x == 0                 &&                 y == 0) ||
        (x == (this->width - 1) && y == (this->height - 1))||
        (x == (this->width - 1) &&                 y == 0) ||
        (x == 0                 && y == (this->height - 1))||
        (x == midX              &&                y == midY)) {
        return true;
    }
    return false;
}

void Board::matchPieces(Player* attacker, Defender* defender)
{
    this->log->debug("Match pieces");
    
    // Attacker pieces
    Piece** attackerWarriors = attacker->getWarriors();
    for (int i = 0; i < attacker->getSize(); i++)
    {
        short x = attackerWarriors[i]->getX();
        short y = attackerWarriors[i]->getY();

        this->log->debug("I: " + std::to_string(i) + "X: " + std::to_string(x) + "Y: " + std::to_string(y));
        this->board[x][y] = attackerWarriors[i];
    }
    
    // Defender pieces
    Piece** defenderWarriors = defender->getWarriors();
    for (int i = 0; i < defender->getSize(); i++)
    {
        short x = defenderWarriors[i]->getX();
        short y = defenderWarriors[i]->getY();

        this->log->debug("I: " + std::to_string(i) + "X: " + std::to_string(x) + "Y: " + std::to_string(y));
        this->board[x][y] = defenderWarriors[i];
    }
    Piece* king = defender->getKing();
    short kingX = king->getX();
    short kingY = king->getY();
    this->board[kingX][kingY] = king;
}

bool Board::checkIntegrity(bool isDefender, short fromX, short fromY, short toX, short toY)
{
    // Not a piece at all
    if (this->board[fromX][fromY] == nullptr)
    {
        return false;
    }
    
    // Not your piece
    if (this->board[fromX][fromY]->isDefender() != isDefender)
    {
        return false;
    }
    
    return true;
}

bool Board::checkBoundaries(short toX, short toY)
{
    if ((toX >= 0 && toX < this->width) &&
        (toY >= 0 && toY < this->height)) {
        return true;
    }
    return false;
}

bool Board::checkFreePath(short fromX, short fromY, short toX, short toY)
{
    short x_dir = fromX - toX;
    short y_dir = fromY - toY;
    
    if (x_dir != 0)
    {
        if (x_dir > 0)
        {
            if ((fromX - 1) > 0)
            {
                for (int x = (fromX - 1); x >= toX; x--)
                {
                    if (this->board[x][toY] != nullptr)
                    {
                        return false;
                    }
                }
            }
        }
        
        if (x_dir < 0)
        {
            if ((fromX + 1) < this->width)
            {
                for (int x = (fromX + 1); x <= toX; x++)
                {
                    if (this->board[x][toY] != nullptr)
                    {
                        return false;
                    }
                }
            }
        }
    }
    
    if (y_dir != 0)
    {
        if (y_dir > 0)
        {
            if ((fromY - 1) > 0)
            {
                for (int y = (fromY - 1); y >= toY; y--)
                {
                    if (this->board[toX][y] != nullptr)
                    {
                        return false;
                    }
                }
            }
        }
        
        if (y_dir < 0)
        {
            if ((fromY + 1) < this->height)
            {
                for (int y = (fromY + 1); y <= toY; y++)
                {
                    if (this->board[toX][y] != nullptr)
                    {
                        return false;
                    }
                }
            }
        }
    }
    
    return true;
}

bool Board::checkIsStraightPath(short fromX, short fromY, short toX, short toY)
{
    short x_dir = fromX - toX;
    short y_dir = fromY - toY;
    short total = 0;
    
    if (x_dir != 0) total++;
    if (y_dir != 0) total++;
    
    return total <= 1;
}

bool Board::checkIsKingsSquare(short fromX, short fromY, short toX, short toY)
{
    if (!this->board[fromX][fromY]->isKing())
    {
        return this->isKingsSquare(toX, toY);
    }
    return false;
}

bool Board::checkIsFreeSquare(short toX, short toY)
{
    if (this->board[toX][toY] != nullptr)
    {
        return false;
    }
    return true;
}

bool Board::movePiece(short fromX, short fromY, short toX, short toY)
{
    if (this->board[fromX][fromY] == nullptr)
    {
        return false;
    }
    
    this->board[fromX][fromY]->setCoord(toX, toY);
    this->board[toX][toY] = this->board[fromX][fromY];
    this->board[fromX][fromY] = nullptr;
    return true;
}

bool Board::checkKingsPosition(short kingsX, short kingsY)
{
    if ((kingsX != this->width / 2) && (kingsY != this->height / 2))
    {
        return this->isKingsSquare(kingsX, kingsY);
    }
    return false;
}

bool Board::checkCheckMate(short kingsX, short kingsY)
{
    bool top = false;
    bool right = false;
    bool bottom = false;
    bool left = false;
    
    if ((kingsX - 1) >= 0)
    {
        if (this->board[kingsX - 1][kingsY] != nullptr) {
            if (!this->board[kingsX - 1][kingsY]->isDefender())
            {
                top = true;
            }
        }
    }
    else
    {
        top = true;
    }
    
    if ((kingsY + 1) < this->height)
    {
        if (this->board[kingsX][kingsY + 1] != nullptr) {
            if (!this->board[kingsX][kingsY + 1]->isDefender())
            {
                right = true;
            }
        }
    }
    else {
        right = true;
    }
    
    if ((kingsX + 1) < this->width)
    {
        if (this->board[kingsX + 1][kingsY] != nullptr) {
            if (!this->board[kingsX + 1][kingsY]->isDefender())
            {
                bottom = true;
            }
        }
    }
    else
    {
        bottom = true;
    }
    
    if ((kingsY - 1) >= 0)
    {
        if (this->board[kingsX][kingsY - 1] != nullptr) {
            if (!this->board[kingsX][kingsY - 1]->isDefender())
            {
                left = true;
            }
        }
    }
    else
    {
        left = true;
    }
    
    if (top && right && bottom && left) return true;
    return false;
}

short Board::checkIsCaptured(bool isDefender, short fromX, short fromY, short toX, short toY)
{
    if (this->checkCaptureAbove(isDefender, toX, toY))
    {
        return 0;
    }
    
    if (this->checkCaptureRight(isDefender, toX, toY))
    {
        return 1;
    }
    
    if (this->checkCaptureBelow(isDefender, toX, toY))
    {
        return 2;
    }
    
    if (this->checkCaptureLeft(isDefender, toX, toY))
    {
        return 3;
    }
    
    return -1;
}

bool Board::checkCaptureAbove(bool isDefender, short toX, short toY)
{
    if ((toY - 2) >= 0)
    {
        if ((this->board[toX][toY - 1] != nullptr) &&
            (this->board[toX][toY - 1]->isDefender() != isDefender) &&
            !this->board[toX][toY - 1]->isKing())
        {
            if ((this->board[toX][toY - 2] != nullptr) && (this->board[toX][toY - 2]->isDefender() == isDefender))
            {
                return true;
            }
        }
    }
    return false;
}

bool Board::checkCaptureBelow(bool isDefender, short toX, short toY)
{
    if ((toY + 2) < this->height)
    {
        if ((this->board[toX][toY + 1] != nullptr) &&
            (this->board[toX][toY + 1]->isDefender() != isDefender) &&
            !this->board[toX][toY + 1]->isKing())
        {
            if ((this->board[toX][toY + 2] != nullptr) && (this->board[toX][toY + 2]->isDefender() == isDefender))
            {
                return true;
            }
        }
    }
    return false;
}

bool Board::checkCaptureRight(bool isDefender, short toX, short toY)
{
    if ((toX + 2) < this->width)
    {
        if ((this->board[toX + 1][toY] != nullptr) && 
            (this->board[toX + 1][toY]->isDefender() != isDefender) &&
            !this->board[toX + 1][toY]->isKing())
        {
            if ((this->board[toX + 2][toY] != nullptr) && (this->board[toX + 2][toY]->isDefender() == isDefender))
            {
                return true;
            }
        }
    }
    return false;
}

bool Board::checkCaptureLeft(bool isDefender, short toX, short toY)
{
    if ((toX - 2) >= 0)
    {
        if ((this->board[toX - 1][toY] != nullptr) &&
            (this->board[toX - 1][toY]->isDefender() != isDefender) &&
            !this->board[toX - 1][toY]->isKing())
        {
            if ((this->board[toX - 2][toY] != nullptr) && (this->board[toX - 2][toY]->isDefender() == isDefender))
            {
                return true;
            }
        }
    }
    return false;
}

bool Board::removePiece(short x, short y)
{
    if (this->board[x][y] == nullptr)
    {
        return false;
    }
    this->board[x][y] = nullptr;
    return true;
}
