//
//  argumentParser.cpp
//  Hnefatafl
//
//  Created by Rasmus Schenström on 2024-04-30.
//

#include "argumentParser.hpp"
#include "game.hpp"

#include <iostream>
#include <iomanip>
#include <regex>

enum Argument {HELP, SIZE, NETWORK, PORT};
ArgumentParser::ArgumentParser()
{
    this->arguments = {
        {"--help    |-h", "                                    ", "Display this help"                      },
        {"--size    |-s", "small|medium(default)|large         ", "Change board size"                      },
        {"--network |-n", "                                    ", "Enable network mode"                    },
        {"--port    |-p", "<PORT_NO>                           ", "Set port number to use in network mode" }
    };
}

Configurations* ArgumentParser::parseArguments(const float VERSION, int argc, const char* argv[])
{
    ArgumentParser* argumentParser = new ArgumentParser();
    Configurations* configurations = new Configurations();
    
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            short matchedArgumentIndex = argumentParser->matchArguments(argv[i]);
            switch (matchedArgumentIndex)
            {
                case Argument::HELP:
                    argumentParser->printHelp(VERSION);
                    delete configurations;
                    configurations = nullptr;
                    break;
                case Argument::SIZE:
                    if (!argumentParser->setSize(configurations, i, argc, argv)) matchedArgumentIndex = -1;
                    i++;
                    break;
                case Argument::NETWORK:
                    configurations->setNetworkEnabled();
                    break;
                case Argument::PORT:
                    if (!argumentParser->setPort(configurations, i, argc, argv)) matchedArgumentIndex = -1;
                    i++;
                    break;
                default:
                    break;
            }
            
            if (matchedArgumentIndex == -1)
            {
                delete configurations;
                configurations = nullptr;
                std::cout << "Invalid input" << std::endl;
                break;
            }
        }
    }
    
    delete argumentParser;;
    return configurations;
}

short ArgumentParser::matchArguments(std::string argument)
{
    short matchedArgumentIndex = -1;
    for (int j = 0; j < getArguments().size(); j++)
    {
        if (std::regex_match(argument, std::regex(getArguments().at(j)[0])))
        {
            matchedArgumentIndex = j;
            break;
        }
    }
    return matchedArgumentIndex;
}

std::vector<std::array<std::string, 4>> ArgumentParser::getArguments()
{
    return this->arguments;
}

void ArgumentParser::printHelp(const float VERSION)
{
    std::cout << std::setprecision(1) << std::fixed;
    std::cout << "\nHnefatafl\nCreator: Rasmus Schenström\nVersion: " << VERSION << "\n\nOptions:\n";
    
    for (auto argument : arguments)
    {
        std::cout << "\t" << argument[0] << " \t" << argument[1] << "\t- " << argument[2] << "\n";
    }
    
    std::cout << std::endl;
}

bool ArgumentParser::setSize(Configurations*& configurations, int i, int argc, const char* argv[])
{
    //if ((i + 1) < argc && std::regex_match(argv[i + 1], std::regex("[0-9]+x[0-9]+")))
    if ((i + 1) < argc && std::regex_match(argv[i + 1], std::regex("small|medium|large")))
    {
        //std::vector<std::string> dimensions = Game::splitString(argv[i + 1], "x");
        ArgumentParser::setSize(configurations, argv[i + 1]);
        return true;
    }
    return false;
}

bool ArgumentParser::setPort(Configurations*& configurations, int i, int argc, const char* argv[])
{
    if ((i + 1) < argc && std::regex_match(argv[i + 1], std::regex("[0-9]+")))
    {
        configurations->setPort(std::stoi(argv[i + 1]));
        return true;
    }
    return false;
}

void ArgumentParser::setSize(Configurations*& configurations, std::string size)
{
    std::vector<short> dimensions;
    if (size == "small")
    {
        dimensions = {9, 9};
    }
    else if (size == "medium")
    {
        dimensions = {11, 11};
    }
    else if (size == "large")
    {
        dimensions = {19, 19};
    }
    
    configurations->setSizeText(size);
    configurations->setWidth(dimensions[0]);
    configurations->setHeight(dimensions[1]);
}
