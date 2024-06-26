//
//  main.cpp
//  Hnefatafl
//
//  Created by Rasmus Schenström on 2024-04-26.
//

#include <vector>
#include <iostream>
#include <regex>
#include <signal.h>

#include "argumentParser.hpp"
#include "configurations.hpp"
#include "constants.hpp"
#include "game.hpp"
#include "network/networking.hpp"

// FUNC
Networking* setupNetwork(Configurations* configurations);
std::string printRules(Configurations* configurations);

// VAR
Networking* networking = nullptr;

void closeNetworking (int s)
{
    if (networking != nullptr) delete networking;
    exit(1);
}

int main(int argc, const char * argv[]) {
    Logger::Initialize(Logger::LogLevel::WARNING);
    const float VERSION = 2.0;
    
    Configurations* configurations = ArgumentParser::parseArguments(VERSION, argc, argv);
    if (configurations == nullptr) return 0;
    
    
    if (configurations->getIsNetworkEnabled())
    {
        networking = setupNetwork(configurations);
        if (networking == nullptr) exit (1);
        
        struct sigaction sigIntHandler;
        sigIntHandler.sa_handler = closeNetworking;
        sigemptyset(&sigIntHandler.sa_mask);
        sigIntHandler.sa_flags = 0;
        sigaction(SIGINT, &sigIntHandler, NULL);
    }
    
    std::string run = printRules(configurations);
    while (std::regex_match(run, std::regex("y|Y")))
    {
        Game* game = new Game(configurations, networking);
        delete game;

        if (!configurations->getIsNetworkEnabled())
        {
            std::cout << "Play again? (Y/n): ";
            getline(std::cin, run);
        }
        else
        {
            run = 'n';
        }
    }
    
    if (networking != nullptr) delete networking;
    delete configurations;
    
    return 0;
}

std::string printRules(Configurations* configurations)
{
    std::string run = "y";
    std::cout << Constants::CLEAR_SCREEN << "                       __   __ __  __ ____ _____ ______ ______ ______ _____ __\n";
    std::cout << "                      / /__/ /  | / / ___/  ___/  __  /__  __/  __  /  ___/  /\n";
    std::cout << "                     /  __  / /||/ / __//  __// /__/ /  / / / /__/ /  __//  /__\n";
    std::cout << "                    /_/  /_/_/ |__/____/__/  /_/  /_/  /_/ /_/  /_/__/  /_____/\n\n";
    
    std::cout << "                                        -= " << Constants::FG_RED_BOLD << "R U L E S" << Constants::RESET_FORMATTING << " =-  \n\n";
    std::cout << "The objective for the " << Constants::DEFENDER_COLOR << "DEFENDER" << Constants::RESET_FORMATTING << " is to get the king (" << Constants::FG_RED_BOLD << "@" << Constants::RESET_FORMATTING  << ") to any of the corners of the board.\n";
    std::cout << "The objective for the " << Constants::ATTACKER_COLOR << "ATTACKER" << Constants::RESET_FORMATTING << " is to capture the king by putting four warriors (" << Constants::FG_RED_BOLD << "!" << Constants::RESET_FORMATTING << ") on each side, perpendicular, of the king (not diagonal).\n\n";
    std::cout << "A warrior can be captured by putting two of the opponents warriors on opposite side of it or by trapping it between a warrior and a kings square.\n";
    std::cout << "Warriors can only move in straight lines and can not be placed on a kings square (" << Constants::FG_RED_BOLD << "X" << Constants::RESET_FORMATTING << ") nor walk throught them.\n\n";
    std::cout << "The game is finished either by completing any of the objectives above or if all the opponents game pieces has been captured.\n\n";
    std::cout << "Current board size: " << std::to_string(configurations->getWidth()) << "x" << std::to_string(configurations->getHeight()) << " (" << configurations->getSizeText() << ")\n";
    std::cout << "Ready to play? (Y/n): ";
    getline(std::cin, run);
    if (run == "") run = "y";
    return run;
}

Networking* setupNetwork(Configurations* configurations)
{
    Networking* networking = nullptr;
    
    std::string input = "";
    std::cout << "\nNETWORK MODE\n";
    std::cout << "Would you like to host the server? [Y/n]:  ";
    getline(std::cin, input);
    if (input == "") input = "y";
    
    if (std::regex_match(input, std::regex("y|Y")))
    {
        std::cout << "Start as " << Constants::ATTACKER_COLOR << "ATTACKER" << Constants::RESET_FORMATTING << "? [Y/n]: ";
        getline(std::cin, input);
        if (input == "") input = "y";
        if (std::regex_match(input, std::regex("n|N"))) configurations->setMe((configurations->getPlayerTurn() + 1) % 2);
        std::string playAs = ((configurations->getMe() + 1) % 2 == 0) ? Constants::DEFENDER_COLOR + "DEFENDER" : Constants::ATTACKER_COLOR  + "ATTACKER";
        std::cout << "You will start as " << playAs << Constants::RESET_FORMATTING << ".\n\n";
        networking = new Networking(true, configurations);
        networking->startSocket();
        networking->sendMsg(configurations->getSizeText());
        networking->recvMsg();
        networking->sendMsg(std::to_string(configurations->getMe()));
        return networking;
    }
    else if (std::regex_match(input, std::regex("n|N")))
    {
        std::cout << "Enter the IP-address of the host? [IPv4: X.X.X.X]:  ";
        getline(std::cin, input);
        
        if (std::regex_match(input, std::regex("[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+")))
        {
            networking = new Networking(false, configurations);
            if (networking->connectTo(input))
            {
                std::string size = networking->recvMsg();
                ArgumentParser::setSize(configurations, size);
                networking->sendMsg("ack");
                std::string playerTurn = networking->recvMsg();
                configurations->setMe((short) (std::stoi(playerTurn) + 1) % 2);
                return networking;
            }
        }
    }
    
    std::cout << "Invalid option. Exiting...\n";
    return nullptr;
}
