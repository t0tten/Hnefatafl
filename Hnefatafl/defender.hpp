//
//  defender.hpp
//  Hnefatafl
//
//  Created by Rasmus Schenström on 2024-04-27.
//

#ifndef defender_hpp
#define defender_hpp

#include "piece.hpp"
#include "player.hpp"
#include "logger/logger.hpp"

class Defender : public Player
{
    public:
        Defender(short sizeWarriors, short width, short height);
        ~Defender();
        virtual void placePieces();
        Piece* getKing();
        virtual std::string getColor();
        virtual std::string getName();

    private:
        Piece* king;

        Logger* log = Logger::GetInstance();
};

#endif /* defender_hpp */
