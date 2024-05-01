//
//  argumentParser.hpp
//  Hnefatafl
//
//  Created by Rasmus Schenström on 2024-04-30.
//

#ifndef argumentParser_hpp
#define argumentParser_hpp

#include <string>

#include "configurations.hpp"

class ArgumentParser
{
    private:
        ArgumentParser();
        
    public:
        static Configurations* parseArguments(const float VERSION, int argc, const char * argv[]);
        static void setSize(Configurations*& configurations, std::string dimensions);
};
#endif /* argumentParser_hpp */
