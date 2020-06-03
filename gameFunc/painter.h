#ifndef PainterClass
#define PainterClass

#include <string>
#include "Tiles.h"

// text format
#define NORMAL_TEXT "\033[0m"
#define BOLD_TEXT "\033[1m"
#define UNDERLINE_TEXT "\033[4m"
#define BLINK_TEXT "\033[5m"
#define REVERSE_TEXT "\033[7m"

// text colour
#define BLACK_TEXT "\033[1;30m"
#define RED_TEXT "\033[31m"
#define ORANGE_TEXT "\033[1;31m"
#define GREEN_TEXT "\033[32m"
#define YELLOW_TEXT "\033[33m"
#define DARKBLUE_TEXT "\033[34m"
#define MAGENTA_TEXT "\033[35m"
#define LIGHTBLUE_TEXT "\033[36m"
#define WHITE_TEXT "\033[37m"

// background colour
#define BLACK_BACKGROUND "\033[40m"
#define RED_BACKGROUND "\033[41m"
#define GREEN_BACKGROUND "\033[42m"
#define YELLOW_BACKGROUND "\033[43m"
#define BLUE_BACKGROUND "\033[44m"
#define MAGENTA_BACKGROUND "\033[45m"
#define CYAN_BACKGROUND "\033[46m"
#define WHITE_BACKGROUND "\033[47m"

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