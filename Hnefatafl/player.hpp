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
        Player(short sizeWarriors);
        ~Player();

        Piece** getWarriors();
        short getSize();
    
        virtual void placePieces();
        virtual std::string getColor();
        virtual std::string getName();
    
    protected:
        Player(short sizeWarriors, std::string color, bool isDefender);
        Piece** warriors;
        short sizeWarriors;
        short warriorsLeft;
        Logger* log = Logger::GetInstance();
};

#endif /* player_hpp */
