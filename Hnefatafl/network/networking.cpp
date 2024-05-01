//
//  Server.cpp
//  Networking
//
//  Created by Rasmus Schenström on 2024-04-30.
//

#include "networking.hpp"
#include <iostream>
 
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <chrono>
#include <thread>

Networking::Networking(bool isServer)
{
    this->isServer = isServer;
    this->port = 8080;
    this->sockA = socket(AF_INET, SOCK_STREAM, 0);
    this->addressA.sin_family = AF_INET;
    this->addressA.sin_port = htons(this->port);
}

Networking::~Networking() {
    std::cout << "RUNNING FUNCTION!" << std::endl;
    this->closeConnection();
}

bool Networking::connectTo(std::string ip_a)
{
    this->isServer = false;
    addressA.sin_addr.s_addr = inet_addr(ip_a.c_str());
    std::cout << "Trying to connect to: " << ip_a << "...\n";

    if (connect(this->sockA, (struct sockaddr*)&addressA, sizeof(addressA)) == -1)
    {
        std::cout << "Couldn't connect to server...\n";
        return false;
    } else{
        this->connected = true;
        return true;
    }
}

void Networking::startSocket()
{
    this->isServer = true;
    this->addressA.sin_addr.s_addr = INADDR_ANY;
    bind(this->sockA, (struct sockaddr*)& this->addressA, sizeof(addressA));
    listen(sockA, 5);

    std::cout << "Waiting for player to connect...\n";
    this->sockB = accept(sockA, (struct sockaddr *) &addressB, &sockBLen);
    char str[INET6_ADDRSTRLEN];
    inet_ntop(AF_INET6, &addressB.sin_addr, str, INET6_ADDRSTRLEN );
    std::cout << "Got connection from IPv4: " << inet_ntoa(addressB.sin_addr) << " , IPv6: " << str << std::endl;
    this->connected = true;
}

int Networking::sendMsg(std::string message)
{
    return (int) send((isServer) ? this->sockB : this->sockA, message.c_str(), message.size(), 0);
}

std::string Networking::recvMsg()
{
    int bytes = 100;
    std::string message = "";
    const short bufferSize = 10;
    while (bytes >= bufferSize)
    {
        char buffer[bufferSize] = { 0 };
        bytes = (int) recv((isServer) ? this->sockB : this->sockA, buffer, sizeof(buffer), 0);
        message += buffer;
        
        if (bytes == 0)
        {
            message = "lost";
        }
    }
    return message;
}

void Networking::closeConnection()
{
    close(this->sockA);
    if (isServer) close(this->sockB);
    this->connected = false;
}

bool Networking::isConnected()
{
    return this->connected;
}
