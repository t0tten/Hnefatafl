//
//  argumentParser.cpp
//  Hnefatafl
//
//  Created by Rasmus Schenström on 2024-04-30.
//

#include "argumentParser.hpp"
#include "game.hpp"

#include <iostream>
#include <regex>

Configurations* ArgumentParser::parseArguments(const float VERSION, int argc, const char * argv[])
{
    Configurations* configurations = new Configurations();
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            if (std::regex_match(argv[i], std::regex("--help|-h")))
            {
                std::cout << "\nHnefatafl\nCreator: Rasmus Schenström\nVersion: v" << VERSION << "\n\nOptions:\n";
                std::cout << "\t--help|-h \t                             \t- Change board size (Eg: 11x11)\n";
                std::cout << "\t--size|-s \t[UN-EVEN NUM]x[UN-EVEN NUM] \t- Change board size (Eg: 11x11)\n";
                std::cout << "\t--network|-n \t                          \t- Network mode\n" << std::endl;
                delete configurations;
                return nullptr;
            }
            else if (std::regex_match(argv[i], std::regex("--size|-s")))
            {
                if (i != (argc - 1) && std::regex_match(argv[i + 1], std::regex("[0-9]+x[0-9]+")))
                {
                    std::vector<std::string> dimensions = Game::splitString(argv[i + 1], "x");
                    ArgumentParser::setSize(configurations, argv[i + 1]);
                    
                    i++;
                }
            }
            else if (std::regex_match(argv[i], std::regex("--network|-n")))
            {
                configurations->setNetworkEnabled();
            }
        }
    }
    
    return configurations;
}

void ArgumentParser::setSize(Configurations*& configurations, std::string size)
{
    std::vector<std::string> dimensions = Game::splitString(size, "x");
    
    short width = std::stoi(dimensions.at(0));
    if (width % 2 == 0) width--;
    if (width < 9) width = 9;
    
    short height = std::stoi(dimensions.at(1));
    if (height % 2 == 0) height--;
    if (height < 9) height = 9;
    
    configurations->setWidth(width);
    configurations->setHeight(height);
}
