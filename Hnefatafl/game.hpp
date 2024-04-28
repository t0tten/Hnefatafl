//
//  game.hpp
//  Hnefatafl
//
//  Created by Rasmus Schenström on 2024-04-27.
//

#ifndef game_hpp
#define game_hpp

#include "board.hpp"
#include "player.hpp"
#include "defender.hpp"
#include "logger/logger.hpp"
#include <string>
#include <vector>

class Game
{
    private:
        Logger* logger;
        Player* attacker;
        Defender* defender;
    
        Board* board;
        short playerTurn;
        bool gameIsRunning;
        short attackerCaptured;
        short defenderCaptured;
        short width;
        short height;
    
        void gameLoop();
        void printGame();
        std::string gatherInput(Player* playerTurn);
        std::vector<short> processInput(Player* playerTurn, std::string input);
    
    public:
        Game(short width, short height);
        ~Game();
    
        static std::vector<std::string> splitString(std::string inputString, std::string delimiter);
};

#endif /* game_hpp */
