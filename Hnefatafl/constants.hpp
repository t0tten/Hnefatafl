//
//  Constants.hpp
//  Hnefatafl
//
//  Created by Rasmus Schenström on 2024-04-29.
//

#ifndef Constants_hpp
#define Constants_hpp

#include <string>

class Constants
{
    public:
        inline static const std::string CLEAR_SCREEN = "\x1B[2J\x1B[H";
        inline static const std::string RESET_FORMATTING = "\033[0m";
        
        inline static const std::string FG_BLUE_BOLD = "\033[1;94m";
        inline static const std::string FG_GREEN_BOLD = "\033[1;32m";
        inline static const std::string FG_RED_BOLD = "\033[1;31m";
        inline static const std::string FG_CYAN_REGULAR = "\033[0;96m";
        
        inline static const std::string BG_GRAY = "\033[0;100m";
        inline static const std::string BG_RED = "\033[1;41m";
    
        inline static const std::string ATTACKER_COLOR = FG_BLUE_BOLD;
        inline static const std::string DEFENDER_COLOR = FG_GREEN_BOLD;
};

#endif /* Constants_hpp */
