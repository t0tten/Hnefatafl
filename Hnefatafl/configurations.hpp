//
//  configurations.hpp
//  Hnefatafl
//
//  Created by Rasmus Schenström on 2024-04-30.
//

#ifndef configurations_hpp
#define configurations_hpp

#include <stdio.h>

class Configurations
{
    short playerTurn;
    short me;
    short width;
    short height;
    bool isNetworkMode;
    
public:
    Configurations();
    
    
    short getPlayerTurn();
    short getMe();
    short getWidth();
    short getHeight();
    bool getIsNetworkEnabled();
    
    void switchStartPlayer();
    void setPlayerTurn(short playerTurn);
    void setMe(short playerTurn);
    void setWidth(short width);
    void setHeight(short height);
    void setNetworkEnabled();
};
#endif /* configurations_hpp */
