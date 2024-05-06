//
//  configurations.hpp
//  Hnefatafl
//
//  Created by Rasmus Schenström on 2024-04-30.
//

#ifndef configurations_hpp
#define configurations_hpp

#include <stdio.h>
#include <string>

class Configurations
{
    short playerTurn;
    short me;
    short width;
    short height;
    std::string size;
    int port;
    bool isNetworkMode;
    
public:
    Configurations();
    
    
    short getPlayerTurn();
    short getMe();
    short getWidth();
    short getHeight();
    std::string getSizeText();
    int getPort();
    bool getIsNetworkEnabled();
    
    void switchStartPlayer();
    void setPlayerTurn(short playerTurn);
    void setMe(short playerTurn);
    void setWidth(short width);
    void setHeight(short height);
    void setSizeText(std::string size);
    void setPort(int port);
    void setNetworkEnabled();
};
#endif /* configurations_hpp */
