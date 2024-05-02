//
//  argumentParser.hpp
//  Hnefatafl
//
//  Created by Rasmus Schenström on 2024-04-30.
//

#ifndef argumentParser_hpp
#define argumentParser_hpp

#include <string>
#include <vector>

#include "configurations.hpp"

class ArgumentParser
{
    private:
        std::vector<std::array<std::string, 4>> arguments;
    
    ArgumentParser();
    short matchArguments(std::string argument);
    
    void printHelp(const float VERSION);
    bool setSize(Configurations*& configurations, int i, int argc, const char* argv[]);
    bool setPort(Configurations*& configurations, int i, int argc, const char* argv[]);
    std::vector<std::array<std::string, 4>> getArguments();
        
    public:
        static Configurations* parseArguments(const float VERSION, int argc, const char* argv[]);
        static void setSize(Configurations*& configurations, std::string dimensions);
};
#endif /* argumentParser_hpp */
