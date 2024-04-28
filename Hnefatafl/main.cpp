//
//  main.cpp
//  Hnefatafl
//
//  Created by Rasmus Schenström on 2024-04-26.
//

#include <iostream>
#include "game.hpp"

#define CLS "\x1B[2J\x1B[H"
#define BLUE_BOLD "\033[1;94m"
#define GREEN_BOLD "\033[1;32m"
#define RED_BOLD "\033[1;31m"
#define RESET_REGULAR "\033[0m"

int main(int argc, const char * argv[]) {
    Logger::Initialize(Logger::LogLevel::WARNING);
    
    
    char run = 'y';
    std::cout << std::string(CLS) << "               __    __ _____ _____ ____    __ _______  _________ _______  _____ __\n";
    std::cout << "             /  /__/  /   __/   __/     | /  /   __   /___   ___/   __   /   __/  /\n";
    std::cout << "            /   __   /   __/   _//  /|  |/  /  /__/  /   /  /  /  /__/  /   _//  /__\n";
    std::cout << "           /__/  /__/_____/___/ /__/ |_____/__/  /__/   /__/  /__/  /__/___/ /_____/\n\n";
    
    std::cout << "\n                                        -= " << std::string(RED_BOLD) << "R U L E S" << std::string(RESET_REGULAR) << " =-  \n\n";
    std::cout << "The objective for the " << std::string(GREEN_BOLD) << "DEFENDER" << std::string(RESET_REGULAR) << " is to get the king (" << std::string(RED_BOLD) << "@" << std::string(RESET_REGULAR) << ") to any of the corners of the board.\n";
    std::cout << "The objective for the " << std::string(BLUE_BOLD) << "ATTACKER" << std::string(RESET_REGULAR) << " is to capture the king by putting a warrior (" << std::string(RED_BOLD) << "!" << std::string(RESET_REGULAR) << ") on each side of the king.\n\n";
    std::cout << "Any of the warriors can be capture by putting two of the opponents warriors on each side of it.\n";
    std::cout << "Warriors can only move in straight lines and can not be placed on a kings square (" << std::string(RED_BOLD) << "X" << std::string(RESET_REGULAR) << ").\n\n";
    std::cout << "The game is finished either by completing any of the objectives above or if all the opponents game pieces has been captured.\n\n";
    std::cout << "Ready to play? (Y/n): ";
    std::cin >> run;
    
    while (run == 'y' || run == 'Y')
    {
        Game* game = new Game();
        delete game;
        std::cout << "Play again? (Y/n): ";
        std::cin >> run;
    }
    
    return 0;
}
