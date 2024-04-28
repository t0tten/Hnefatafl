//
//  piece.hpp
//  Hnefatafl
//
//  Created by Rasmus Schenström on 2024-04-27.
//

#ifndef piece_hpp
#define piece_hpp

#include "logger/logger.hpp"
#include <string>

class Piece
{
    public:
        enum PieceType { WARRIOR, KING };

        Piece(PieceType pieceTypme, std::string color, bool isDefender);
        ~Piece();

        std::string getSign();
        void setCoord(short x, short y);
        short getX();
        short getY();
        std::string getColor();
        bool isDefender();
        bool isKing();

    private:
        short x, y;
        std::string color;
        PieceType pieceType;
        bool defender;

        Logger* log = Logger::GetInstance();
};

#endif /* piece_hpp */
