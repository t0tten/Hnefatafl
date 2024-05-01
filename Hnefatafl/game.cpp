//
//  game.cpp
//  Hnefatafl
//
//  Created by Rasmus Schenström on 2024-04-27.
//

#include <iostream>
#include <regex>

#include "configurations.hpp"
#include "constants.hpp"
#include "game.hpp"
#include "network/networking.hpp"

Game::Game(Configurations* configurations, Networking* networking)
{
    this->logger = Logger::GetInstance();
    
    this->title = "H N E F A T A F L";
    this->configurations = configurations;
    this->networking = networking;
    this->width = configurations->getWidth();
    this->height = configurations->getHeight();
    
    this->attackerCaptured = 0;
    this->defenderCaptured = 0;
    
    this->playerTurn = configurations->getPlayerTurn();
    this->gameIsRunning = true;
    this->isNetworkEnabled = configurations->getIsNetworkEnabled();
    
    this->attacker = new Player(6*4, width, height);
    this->attacker->placePieces();
    
    this->defender = new Defender(12, width, height);
    this->defender->placePieces();
    
    this->board = new Board(width, height);
    this->board->placePiecesOnBoard(this->attacker, this->defender);
    
    this->gameLoop();
}

Game::~Game()
{
    delete this->board;
}

void Game::gameLoop()
{
    std::string input = "";
    Player* playerTurn = (this->getPlayerTurn() == 0) ? this->attacker : this->defender;
    while (gameIsRunning)
    {
        std::cout << this->generateTitleHeader();
        std::vector<short> moveCoords = this->processInput(playerTurn, input);
        this->board->printBoard(moveCoords, this->attackerCaptured, this->defenderCaptured);
        if (gameIsRunning)
        {
            playerTurn = (this->getPlayerTurn() == 0) ? this->attacker : this->defender;
            input = gatherInput(playerTurn);
        }
    }
}

std::string Game::generateTitleHeader()
{
    std::string padding = " ";
    short titleAdding = 0;
    if (this->width > this->title.size()) titleAdding = (this->title.size() / 4);
    for (int i = 0; i < ((this->width/2) + titleAdding); i++) padding += " ";
    return Constants::CLEAR_SCREEN + "\n" + padding + Constants::FG_RED_BOLD + title + Constants::RESET_FORMATTING + "\n";
}

short Game::getPlayerTurn()
{
    return this->playerTurn % 2;
}

std::string Game::gatherInput(Player* playerTurn)
{
    std::cout << "\nPlayer turn: " << playerTurn->getColor() << playerTurn->getName() << Constants::RESET_FORMATTING;
    if (this->isNetworkEnabled)
    {
        if (this->getPlayerTurn() != this->configurations->getMe()) std::cout << " (opponent)";
        else                                                        std::cout << " (you)";
    }
    std::cout << std::endl;
    
    std::string input;
    if (this->isNetworkEnabled && this->getPlayerTurn() != this->configurations->getMe())
    {
        std::cout << "Waiting for opponent to finish the move...\n";
        input = networking->recvMsg();
        if (input == "lost")
        {
            std::cout << "Lost connection to the server\n";
            this->gameIsRunning = false;
            this->networking->closeConnection();
        }
    }
    else
    {
        std::cout << "Move Piece (x,y -> x,y): ";
        std::getline(std::cin, input);
    }
    return input;
}

std::string Game::checkInputs(bool isDefender, short fromX, short fromY, short toX, short toY)
{
    if (!this->board->checkIntegrity(isDefender, fromX, fromY, toX, toY))   return "NOT A VIABLE MOVE";
    if (!this->board->checkBoundaries(toX, toY))                            return "OUT OF BOUNDS OF MAP";
    if (!this->board->checkIsFreeSquare(toX, toY))                          return "SQUARE ALREADY OCCUPIED";
    if (!this->board->checkIsStraightPath(fromX, fromY, toX, toY))          return "CAN ONLY MOVE IN STRAIGHT LINES";
    if (!this->board->checkFreePath(fromX, fromY, toX, toY))                return "NOT A FREE PATH";
    if (this->board->checkIsKingsSquare(fromX, fromY, toX, toY))            return "WARRIOR NOT ALLOWED ON A KINGS SQUARE";
    return "";
}

bool Game::checkWinner()
{
    if (this->board->checkKingsPosition(this->defender->getKing()->getX(), this->defender->getKing()->getY()) ||
       ((this->attacker->getSize() - this->attackerCaptured) == 0) ||
        this->board->checkCheckMate(this->defender->getKing()->getX(), this->defender->getKing()->getY()))
    {
        return true;
    }
    return false;
}

std::vector<short> Game::checkIfCapture(bool isDefender, short fromX, short fromY, short toX, short toY)
{
    std::vector<short> captured = {-1, -1};
    short direction = this->board->checkIsCaptured(isDefender, fromX, fromY, toX, toY);
    if (direction != -1)
    {
        short removeX = toX;
        short removeY = toY;
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
        captured = {removeX, removeY};
        this->board->removePiece(removeX, removeY);
        if (isDefender) this->attackerCaptured++;
        else            this->defenderCaptured++;
    }
    return captured;
}


std::string Game::removeWhitespaces(std::string input)
{
    std::string sanitized;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] != ' ')
        {
            sanitized += input[i];
        }
    }
    return sanitized;
}

std::vector<short> Game::processInput(Player* playerTurn, std::string input)
{
    std::cout << "\nInput: " << input << std::endl;
    
    std::vector<short> moveCoords = {-1, -1, -1, -1, -1, -1};
    if (std::regex_match(input, std::regex(this->inputRegex)))
    {
        std::string sanitized = removeWhitespaces(input);
        std::vector<std::string> coords     = this->splitString(sanitized, "->");
        std::vector<std::string> moveFrom   = this->splitString(coords.at(0), ",");
        std::vector<std::string> moveTo     = this->splitString(coords.at(1), ",");
        
        Defender* defender = dynamic_cast<Defender*>(playerTurn);
        bool isDefender = (defender != nullptr) ? true : false;
        
        std::string message = this->checkInputs(isDefender, std::stoi(moveFrom.at(0)), std::stoi(moveFrom.at(1)), std::stoi(moveTo.at(0)), std::stoi(moveTo.at(1)));
        if (message == "")
        {
            if (this->isNetworkEnabled && this->getPlayerTurn() == this->configurations->getMe()) this->networking->sendMsg(input);
            this->board->movePiece(std::stoi(moveFrom.at(0)), std::stoi(moveFrom.at(1)), std::stoi(moveTo.at(0)), std::stoi(moveTo.at(1)));
            this->playerTurn++;
            
            moveCoords[0] = std::stoi(moveFrom.at(0));
            moveCoords[1] = std::stoi(moveFrom.at(1));
            moveCoords[2] = std::stoi(moveTo.at(0));
            moveCoords[3] = std::stoi(moveTo.at(1));
            Player* opponent = (isDefender) ? this->attacker : this->defender;
            
            message = playerTurn->getColor() + playerTurn->getName() + Constants::RESET_FORMATTING;
            if (this->checkWinner())
            {
                if (this->isNetworkEnabled)
                {
                    if (this->getPlayerTurn() != this->configurations->getMe()) std::cout << " (opponent)";
                    else                                                        std::cout << " (you)";
                }
                message += " HAS WON THE GAME!";
                this->gameIsRunning = false;
            }
            else
            {
                message += " MOVED (" + std::to_string(std::stoi(moveFrom.at(0))) + "," + std::to_string(std::stoi(moveFrom.at(1)))+ ") TO (" + std::to_string(std::stoi(moveTo.at(0))) + "," + std::to_string(std::stoi(moveTo.at(1))) + ")";
                
                std::vector<short> captured = checkIfCapture(isDefender, std::stoi(moveFrom.at(0)), std::stoi(moveFrom.at(1)), std::stoi(moveTo.at(0)), std::stoi(moveTo.at(1)));
                if (captured.at(0) != -1)
                {
                    moveCoords[4] = captured[0];
                    moveCoords[5] = captured[1];
                    message += " AND CAPTURED " + opponent->getColor() + opponent->getName() + "S" + Constants::RESET_FORMATTING + " PIECE AT (" + std::to_string(captured[0]) + "," + std::to_string(captured[1]) + ")";
                }
            }
        }
        std::cout << "Message: " << message << std::endl << std::endl;
    }
    return moveCoords;
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
