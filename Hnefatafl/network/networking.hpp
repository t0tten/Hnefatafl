//
//  Server.hpp
//  Networking
//
//  Created by Rasmus Schenström on 2024-04-30.
//

#ifndef Server_hpp
#define Server_hpp

#include <unistd.h>
#include <arpa/inet.h>
#include <string>

class Networking
{
private:
    short port;
    int sockA, sockB;
    sockaddr_in addressA, addressB;
    socklen_t sockBLen;
    bool isServer;
    bool connected;

public:
    Networking(bool isServer);
    ~Networking();
    
    int sendMsg(std::string message);
    std::string recvMsg();
    
    void startSocket();
    bool connectTo(std::string ip_a);
    
    void closeConnection();
    bool isConnected();
};

#endif /* Server_hpp */
