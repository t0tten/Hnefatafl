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
        std::string title;
        const std::string inputRegex = "[ ]*[0-9]+[ ]*,[ ]*[0-9]+[ ]*-[ ]*>[ ]*[0-9]+[ ]*,[ ]*[0-9]+[ ]*";
    
        void gameLoop();
    
        std::string removeWhitespaces(std::string input);
        std::string gatherInput(Player* playerTurn);
        std::vector<short> processInput(Player* playerTurn, std::string input);
        std::string generateTitleHeader();
    
        std::string checkInputs(bool isDefender, short fromX, short fromY, short toX, short toY);
        bool checkWinner();
        std::vector<short> checkIfCapture(bool isDefender, short fromX, short fromY, short toX, short toY);
    
    public:
        Game(short width, short height);
        ~Game();
    
        static std::vector<std::string> splitString(std::string inputString, std::string delimiter);
};

#endif /* game_hpp */
