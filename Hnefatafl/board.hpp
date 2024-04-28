//
//  board.hpp
//  Hnefatafl
//
//  Created by Rasmus Schenström on 2024-04-26.
//

#ifndef board_hpp
#define board_hpp

#include <iostream>
#include <vector>
#include "player.hpp"
#include "defender.hpp"
#include "logger/logger.hpp"
#include "piece.hpp"

class Board
{
    private:
        Logger* log = Logger::GetInstance();

        short width, height;
        Piece*** board;

        bool isKingsSquare(short x, short y);
        bool checkCaptureAbove(bool isDefender, short toX, short toY);
        bool checkCaptureBelow(bool isDefender, short toX, short toY);
        bool checkCaptureRight(bool isDefender, short toX, short toY);
        bool checkCaptureLeft(bool isDefender, short toX, short toY);
    
        void printBoardHeader();

    public:
        Board(short width, short height);
        ~Board();
    
        void printBoard(std::vector<short> moveCoords, short attackerCaptured, short defenderCaptured);
        Player* getPlayer();
    
        void matchPieces(Player* attacker, Defender* defender);
        
        bool checkBoundaries(short toX, short toY);
        bool checkFreePath(short fromX, short fromY, short toX, short toY);
        bool checkIntegrity(bool isDefender, short fromX, short fromY, short toX, short toY);
        bool checkIsKingsSquare(short fromX, short fromY, short toX, short toY);
        bool checkIsFreeSquare(short toX, short toY);
        bool checkIsStraightPath(short fromX, short fromY, short toX, short toY);
        short checkIsCaptured(bool isDefender, short fromX, short fromY, short toX, short toY);
    
        bool checkKingsPosition(short kingsX, short kingsY);
        bool checkCheckMate(short kingsX, short kingsY);
    
        bool movePiece(short fromX, short fromY, short toX, short toY);
        bool removePiece(short x, short y);
};

#endif /* board_hpp */
