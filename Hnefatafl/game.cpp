//
//  game.cpp
//  Hnefatafl
//
//  Created by Rasmus Schenström on 2024-04-27.
//

#include "game.hpp"
#include <iostream>
#include <regex>

#define RED_BOLD        "\033[1;31m"
//#define RED_BOLD        ""

#define RESET_REGULAR "\033[0m"
//#define RESET_REGULAR ""

#define CLS             "\x1B[2J\x1B[H"
//#define CLS             ""

Game::Game(short width, short height)
{
    this->width = width;
    this->height = height;
    
    this->logger = Logger::GetInstance();
    this->attackerCaptured = 0;
    this->defenderCaptured = 0;
    
    this->playerTurn = 0;
    this->gameIsRunning = true;
    
    this->attacker = new Player(6*4, width, height);
    this->attacker->placePieces();
    
    this->defender = new Defender(12, width, height);
    this->defender->placePieces();
    
    this->board = new Board(width, height);
    this->board->matchPieces(this->attacker, this->defender);
    
    this->gameLoop();
}

Game::~Game()
{
    delete this->board;
}

void Game::gameLoop()
{
    std::string input = "";
    Player* playerTurn = this->attacker;
    while (gameIsRunning)
    {
        std::string title = "H N E F A T A F L";
        std::string padding = " ";
        short titleAdding = 0;
        if (this->width > title.size()) titleAdding = (title.size() / 4);
        for (int i = 0; i < ((this->width/2) + titleAdding); i++) padding += " ";
        std::cout << std::string(CLS) << "\n" << padding << std::string(RED_BOLD) << title << std::string(RESET_REGULAR) << std::endl;
        
        this->processInput(playerTurn, input);
        this->board->printBoard(this->attackerCaptured, this->defenderCaptured);
        if (gameIsRunning)
        {
            if ((this->playerTurn % 2) == 0)
            {
                playerTurn = this->attacker;
            }
            else
            {
                playerTurn = this->defender;
            }
            input = gatherInput(playerTurn);
        }
    }
}

void Game::printGame() {}

std::string Game::gatherInput(Player* playerTurn)
{
    std::cout << "\nPlayer turn: " << playerTurn->getColor() << playerTurn->getName() << std::string(RESET_REGULAR) << "\nMove Piece (x,y -> x,y): ";
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void Game::processInput(Player* playerTurn, std::string input)
{
    std::cout << "\nInput: " << input << std::endl;
    std::string message = "";
    if (std::regex_match(input, std::regex("[ ]*[0-9]+[ ]*,[ ]*[0-9]+[ ]*-[ ]*>[ ]*[0-9]+[ ]*,[ ]*[0-9]+[ ]*")))
    {
        message = playerTurn->getColor() + playerTurn->getName() + std::string(RESET_REGULAR);
        
        // Remove whitespaces
        std::string sanitized = "";
        for (int i = 0; i < input.size(); i++)
        {
            if (input[i] != ' ')
            {
                sanitized += input[i];
            }
        }
        this->logger->debug(sanitized);
        
        // Get coords
        std::vector<std::string> coords = this->splitString(sanitized, "->");
        std::vector<std::string> moveFrom = this->splitString(coords.at(0), ",");
        std::vector<std::string> moveTo = this->splitString(coords.at(1), ",");
        
        Defender* defender = dynamic_cast<Defender*>(playerTurn);
        bool isDefender = (defender != nullptr) ? true : false;
        
        // Check movebility
        if (this->board->checkIntegrity(isDefender, std::stoi(moveFrom.at(0)), std::stoi(moveFrom.at(1)), std::stoi(moveTo.at(0)), std::stoi(moveTo.at(1))))
        {
            if (this->board->checkBoundaries(std::stoi(moveTo.at(0)), std::stoi(moveTo.at(1))))
            {
                if (this->board->checkIsFreeSquare(std::stoi(moveTo.at(0)), std::stoi(moveTo.at(1))))
                {
                    if (this->board->checkIsStraightPath(std::stoi(moveFrom.at(0)), std::stoi(moveFrom.at(1)), std::stoi(moveTo.at(0)), std::stoi(moveTo.at((1)))))
                    {
                        if (this->board->checkFreePath(std::stoi(moveFrom.at(0)), std::stoi(moveFrom.at(1)), std::stoi(moveTo.at(0)), std::stoi(moveTo.at(1))))
                        {
                            if (!this->board->checkIsKingsSquare(std::stoi(moveFrom.at(0)), std::stoi(moveFrom.at(1)), std::stoi(moveTo.at(0)), std::stoi(moveTo.at(1))))
                            {
                                this->board->movePiece(std::stoi(moveFrom.at(0)), std::stoi(moveFrom.at(1)), std::stoi(moveTo.at(0)), std::stoi(moveTo.at(1)));
                                this->playerTurn++;
                                
                                // Check capture
                                short direction = this->board->checkIsCaptured(isDefender, std::stoi(moveFrom.at(0)), std::stoi(moveFrom.at(1)), std::stoi(moveTo.at(0)), std::stoi(moveTo.at(1)));
                                
                                Player* opponent = this->defender;
                                if (isDefender)
                                {
                                    opponent = this->attacker;
                                }
                                
                                
                                if (direction != -1)
                                {
                                    short removeX = std::stoi(moveTo.at(0));
                                    short removeY = std::stoi(moveTo.at(1));
                                    switch (direction)
                                    {
                                        case 0: removeY -= 1;
                                            break;
                                        case 1: removeX += 1;
                                            break;
                                        case 2: removeY += 1;
                                            break;
                                        case 3: removeX -= 1;
                                            break;
                                        default:
                                            break;
                                    }
                                    
                                    this->board->removePiece(removeX, removeY);
                                    if (isDefender)
                                    {
                                        this->attackerCaptured++;
                                    } else
                                    {
                                        this->defenderCaptured++;
                                    }
                                    message += " CAPTURED " + opponent->getColor() + opponent->getName() + "S" +  + RESET_REGULAR + " PIECE AT COORD (" + std::to_string(removeX) + "," + std::to_string(removeY) + ")";
                                } else {
                                    message += " MOVED (" + std::to_string(std::stoi(moveFrom.at(0))) + "," + std::to_string(std::stoi(moveFrom.at(1)))+ ") TO (" + std::to_string(std::stoi(moveTo.at(0))) + "," + std::to_string(std::stoi(moveTo.at(1))) + ")";
                                }
                                
                                // Check winners
                                if (this->board->checkKingsPosition(this->defender->getKing()->getX(), this->defender->getKing()->getY()) || this->attacker->getSize() == 0)
                                {
                                    this->gameIsRunning = false;
                                    message = "DEFENDER HAS WON THE GAME!";
                                }
                                
                                if (this->board->checkCheckMate(this->defender->getKing()->getX(), this->defender->getKing()->getY()) || this->defender->getSize() == 0)
                                {
                                    this->gameIsRunning = false;
                                    message = "ATTACKER HAS WON THE GAME!";
                                }
                            }
                            else
                            {
                                message = "WARRIOR NOT ALLOWED ON A KINGS SQUARE";
                            }
                        }
                        else
                        {
                            message = "NOT A FREE PATH";
                        }
                    }
                    else
                    {
                        message = "CAN ONLY MOVE IN STRAIGHT LINES";
                    }
                }
                else
                {
                    message = "SQUARE ALREADY OCCUPIED";
                }
            }
            else
            {
                message = "OUT OF BOUNDS OF MAP";
            }
        }
        else
        {
            message = "NOT A VIABLE MOVE";
        }
    }
    std::cout << "Message: " << message << std::endl << std::endl;
}

std::vector<std::string> Game::splitString(std::string inputString, std::string delimiter)
{
    std::vector<std::string> array;
    size_t pos = 0;
    while ((pos = inputString.find(delimiter)) != std::string::npos) {
        array.push_back(inputString.substr(0, pos));
        inputString.erase(0, pos + delimiter.length());
    }
    array.push_back(inputString);
    return array;
}
