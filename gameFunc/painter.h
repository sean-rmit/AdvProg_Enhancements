#ifndef PainterClass
#define PainterClass

#include <string>
#include "Tiles.h"

// text format
#define BOLD_TEXT "\033[1m"

// text colour
#define BLACK_TEXT "\033[1;30m"
#define RED_TEXT "\033[31m"
#define ORANGE_TEXT "\033[0;91m"
#define GREEN_TEXT "\033[32m"
#define YELLOW_TEXT "\033[33m"
#define DARKBLUE_TEXT "\033[34m"
#define LIGHTBLUE_TEXT "\033[36m"

// background colour
#define BLACK_BACKGROUND "\033[0;100m"
#define RED_BACKGROUND "\033[41m"
#define ORANGE_BACKGROUND "\033[0;101m"
#define GREEN_BACKGROUND "\033[42m"
#define YELLOW_BACKGROUND "\033[43m"
#define DARKBLUE_BACKGROUND "\033[44m"
#define LIGHTBLUE_BACKGROUND "\033[46m"

// reset
#define RESET "\033[0m"

class Painter {
public:
    Painter();
    ~Painter();

    std::string paintTile(char tile);
    std::string paintWallTile(char actualTile, char templateTile);
    std::string paintString(std::string s, std::string colour);
    
private:
};


#endif // Painter