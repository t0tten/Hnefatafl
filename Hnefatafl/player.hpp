//
//  player.hpp
//  Hnefatafl
//
//  Created by Rasmus Schenström on 2024-04-27.
//

#ifndef player_hpp
#define player_hpp

#include "piece.hpp"
#include "logger/logger.hpp"

class Player
{
    public:
        Player(short width, short height);
        ~Player();

        Piece** getWarriors();
        short getSize();
    
        virtual void placePieces();
        virtual std::string getColor();
        virtual std::string getName();
    
    protected:
        Player(std::string color, bool isDefender, short width, short height);
        Piece** warriors;
        short sizeWarriors;
        short warriorsLeft;
        short width;
        short height;
        Logger* log = Logger::GetInstance();
};

#endif /* player_hpp */
