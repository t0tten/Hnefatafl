//
//  main.cpp
//  Hnefatafl
//
//  Created by Rasmus Schenström on 2024-04-26.
//

#include <iostream>
#include "game.hpp"

int main(int argc, const char * argv[]) {
    Logger::Initialize(Logger::LogLevel::WARNING);
    
    char run = 'y';
    while (run == 'y' || run == 'Y')
    {
        Game* game = new Game();
        delete game;
        std::cout << "Play again? (Y/n): ";
        std::cin >> run;
    }
    
    return 0;
}
