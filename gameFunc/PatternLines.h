#ifndef PlayerPatternLines
#define PlayerPatternLines

#include "Line.h"
#include "Tiles.h"
#include "Wall.h"
#include "BoxLid.h"

#define NORMAL_PATTERN_LINES_NUM 5
#define SIX_TILE_MODE_PATTERN_LINES_NUM    6

class PatternLines {
public:

    // Constructor
    PatternLines(bool sixTileMode);
    // Deconstructor
    ~PatternLines();

    // getter for patternLinesNum
    int getPatternLinesNum();

    // Get line object at given index
    linePtr getLine(int index);

private:
    linePtr *patternLines;
    int patternLinesNum;
    bool sixTileMode;
};

typedef PatternLines* patternLinesPtr;

#endif // PlayerPatternLines