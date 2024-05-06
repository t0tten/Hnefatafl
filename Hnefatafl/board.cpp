//
//  board.cpp
//  Hnefatafl
//
//  Created by Rasmus Schenström on 2024-04-26.
//

#include <iostream>

#include "board.hpp"
#include "constants.hpp"

Board::Board(short width, short height)
{
    this->log->info("Board constructor");
    this->width = width;
    this->height = height;
    
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

std::string Board::getBoardHeader()
{
    std::string header = "";
    short numLoops = (short)this->width / 10;
    for (int j = 0; j <= numLoops; j++)
    {
        header += "   ";
        for (int x = 0; x < this->width; x++)
        {
            if (numLoops > 0 && j == 0)
            {
                std::string numStr = " ";
                if (x > 9) {
                    short tmpX = (short) x / 10;
                    numStr = std::to_string(tmpX);
                }
                header += " " + numStr;
            }
            else
            {
                short tmpX = (x < 10) ? x : x - 10;
                header += " " + std::to_string(tmpX);
            }
        }
        header += "\n";
    }
    return header;
}

std::string Board::getPaddingLeft(short y)
{
    std::string padding = " ";
    if (y < 10) {
        padding += " ";
    }
    padding += std::to_string(y) + "|";
    return padding;
}

bool Board::shouldApplyBackground(short moveDiff, short num1, short comp1, short num2, short comp2, short comp3)
{
    bool shouldSetBackground = false;
    if (moveDiff != 0)
    {
        if ((num1 == comp1 && num2 >= comp2 && num2 <= comp3) ||
            (num1 == comp1 && num2 >= comp3 && num2 <= comp2))
        {
            shouldSetBackground = true;
        }
    }
    return shouldSetBackground;
}

std::string Board::applyBackground(std::vector<short> moveCoords, short x, short y)
{
    std::string background = "";
    if (moveCoords.at(0) != -1)
    {
        short xMove = moveCoords.at(0) - moveCoords.at(2);
        short yMove = moveCoords.at(1) - moveCoords.at(3);
        if (x == moveCoords.at(0) && y == moveCoords.at(1)) return Constants::BG_GRAY;
        if (x == moveCoords.at(4) && y == moveCoords.at(5)) return Constants::BG_RED;
        else if (this->shouldApplyBackground(xMove, y, moveCoords.at(1), x, moveCoords.at(0), moveCoords.at(2)) ||
            this->shouldApplyBackground(yMove, x, moveCoords.at(0), y, moveCoords.at(1), moveCoords.at(3)))
        {
            return Constants::BG_GRAY;
        }
    }
    return "";
}

std::string Board::getBoardRow(short y, std::vector<short> moveCoords)
{
    std::string row = "";
    for (int x = 0; x < this->width; x++)
    {
        std::string background = this->applyBackground(moveCoords, x, y);
        Piece* piece = this->board[x][y];
        if (piece != nullptr)
        {
            row += this->board[x][y]->getColor() + this->board[x][y]->getSign() + Constants::RESET_FORMATTING;;
        }
        else
        {
            if (this->isKingsSquare(x, y))  row += Constants::FG_CYAN_REGULAR + "X";
            else                            row += background + "_";
        }
        
        short xMove = moveCoords.at(0) - moveCoords.at(2);
        if (xMove == 0) row += Constants::RESET_FORMATTING;
        if (x == moveCoords[4] && y == moveCoords[5]) row += Constants::RESET_FORMATTING;
        row += "|";
        if (xMove != 0) row += Constants::RESET_FORMATTING;
    }
    return row;
}

std::string Board::getPlayerLosses(std::string title, short titleRow, short y, short captured, std::string color)
{
    if (y == titleRow) return " " + title;
    
    std::string data = "";
    if (y == titleRow + 1)
    {
        for (int i = 0; i < captured; i++)
        {
            data += "!";
        }
        return " [" + color + data + Constants::RESET_FORMATTING + "]";
    }
    
    return "";
}

void Board::printBoard(std::vector<short> moveCoords, short attackerCaptured, short defenderCaptured)
{
    std::cout << this->getBoardHeader();
    for (int y = 0; y < this->height; y++)
    {
        std::cout << this->getPaddingLeft(y);
        std::cout << this->getBoardRow(y, moveCoords);
        std::cout << this->getPlayerLosses("ATTACKER", 0, y, attackerCaptured, Constants::ATTACKER_COLOR);
        std::cout << this->getPlayerLosses("DEFENDER", 3, y, defenderCaptured, Constants::DEFENDER_COLOR);
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

void Board::placePiecesOnBoard(Piece* piece)
{
    short x = piece->getX();
    short y = piece->getY();
    this->board[x][y] = piece;
}

void Board::placePlayerPiecesOnBoard(Player* player)
{
    std::cout << player->getSize() << std::endl;
    Piece** playerWarriors = player->getWarriors();
    for (int i = 0; i < player->getSize(); i++)
    {
        this->placePiecesOnBoard(playerWarriors[i]);
    }
}

void Board::placePiecesOnBoard(Player* attacker, Defender* defender)
{
    this->log->debug("Match pieces");
    this->placePlayerPiecesOnBoard(attacker);
    this->placePlayerPiecesOnBoard(defender);
    this->placePiecesOnBoard(defender->getKing());
}

bool Board::checkIntegrity(bool isDefender, short fromX, short fromY, short toX, short toY)
{
    if (this->board[fromX][fromY] == nullptr)
    {
        return false;
    }
    
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
                    if (this->board[x][toY] != nullptr || (this->isKingsSquare(x, toY) && !this->board[fromX][fromY]->isKing()))
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
                    if (this->board[x][toY] != nullptr || (this->isKingsSquare(x, toY) && !this->board[fromX][fromY]->isKing()))
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
                    if (this->board[toX][y] != nullptr || (this->isKingsSquare(toX, y) && !this->board[fromX][fromY]->isKing()))
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
                    if (this->board[toX][y] != nullptr || (this->isKingsSquare(toX, y) && !this->board[fromX][fromY]->isKing()))
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
            if (((this->board[toX][toY - 2] != nullptr) && 
                 (this->board[toX][toY - 2]->isDefender() == isDefender)) || this->isKingsSquare(toX, toY - 2))
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
            if (((this->board[toX][toY + 2] != nullptr) && 
                 (this->board[toX][toY + 2]->isDefender() == isDefender)) || this->isKingsSquare(toX, toY + 2))
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
            if (((this->board[toX + 2][toY] != nullptr) && 
                 (this->board[toX + 2][toY]->isDefender() == isDefender)) || this->isKingsSquare(toX + 2, toY))
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
            if (((this->board[toX - 2][toY] != nullptr) && 
                 (this->board[toX - 2][toY]->isDefender() == isDefender)) || this->isKingsSquare(toX - 2, toY))
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
