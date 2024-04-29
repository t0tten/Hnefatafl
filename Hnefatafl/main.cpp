//
//  main.cpp
//  Hnefatafl
//
//  Created by Rasmus Schenström on 2024-04-26.
//

#include <vector>
#include <iostream>
#include <regex>

#include "constants.hpp"
#include "game.hpp"

int main(int argc, const char * argv[]) {
    Logger::Initialize(Logger::LogLevel::WARNING);
    
    short width = 11;
    short height = 11;
    
    if (argc > 1)
    {
        if (std::regex_match(argv[1], std::regex("--help|-h")))
        {
            std::cout << "\nHnefatafl\nCreator: Rasmus Schenström\n\nOptions:\n\t[UN-EVEN NUM]x[UN-EVEN NUM] \t- Change board size (Eg: 11x11)\n" << std::endl;
            return 0;
        }
        else if (std::regex_match(argv[1], std::regex("[0-9]+x[0-9]+")))
        {
            std::cout << "CHANGE SIZE!" << std::endl;
            std::vector<std::string> dimensions = Game::splitString(argv[1], "x");
            
            width = std::stoi(dimensions.at(0));
            if (width % 2 == 0) width--;
            if (width < 9) width = 9;
            
            height = std::stoi(dimensions.at(1));
            if (height % 2 == 0) height--;
            if (height < 9) height = 9;
        }
    }
    
    char run = 'y';
    std::cout << Constants::CLEAR_SCREEN << "                       __   __ __  __ ____ _____ ______ ______ ______ _____ __\n";
    std::cout << "                      / /__/ /  | / / ___/  ___/  __  /__  __/  __  /  ___/  /\n";
    std::cout << "                     /  __  / /||/ / __//  __// /__/ /  / / / /__/ /  __//  /__\n";
    std::cout << "                    /_/  /_/_/ |__/____/__/  /_/  /_/  /_/ /_/  /_/__/  /_____/\n\n";
    
    std::cout << "                                        -= " << Constants::FG_RED_BOLD << "R U L E S" << Constants::RESET_FORMATTING << " =-  \n\n";
    std::cout << "The objective for the " << Constants::DEFENDER_COLOR << "DEFENDER" << Constants::RESET_FORMATTING << " is to get the king (" << Constants::FG_RED_BOLD << "@" << Constants::RESET_FORMATTING  << ") to any of the corners of the board.\n";
    std::cout << "The objective for the " << Constants::ATTACKER_COLOR << "ATTACKER" << Constants::RESET_FORMATTING << " is to capture the king by putting four warriors (" << Constants::FG_RED_BOLD << "!" << Constants::RESET_FORMATTING << ") on each side, perpendicular, of the king (not diagonal).\n\n";
    std::cout << "A warrior can be captured by putting two of the opponents warriors on opposite side of it.\n";
    std::cout << "Warriors can only move in straight lines and can not be placed on a kings square (" << Constants::FG_RED_BOLD << "X" << Constants::RESET_FORMATTING << ").\n\n";
    std::cout << "The game is finished either by completing any of the objectives above or if all the opponents game pieces has been captured.\n\n";
    std::cout << "Current board size: " << std::to_string(width) << "x" << std::to_string(height) << "\n";
    std::cout << "Ready to play? (Y/n): ";
    std::cin >> run;
    
    while (run == 'y' || run == 'Y')
    {
        Game* game = new Game(width, height);
        delete game;
        std::cout << "Play again? (Y/n): ";
        std::cin >> run;
    }
    
    return 0;
}
