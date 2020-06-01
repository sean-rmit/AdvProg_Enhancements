#ifndef PlayerPatternLines
#define PlayerPatternLines

#include "Line.h"
#include "Tiles.h"
#include "Wall.h"
#include "BoxLid.h"

#define NORMAL_PATTERN_LINES_NUM 5
#define ADV_PATTERN_LINES_NUM    6

class PatternLines {
public:

    // Constructor
    PatternLines(bool advMode);
    // Deconstructor
    ~PatternLines();

    // Copy constructor
    PatternLines(PatternLines& other);

    // getter for patternLinesNum
    int getPatternLinesNum();

    // Get line object at given index
    linePtr getLine(int index);

private:
    linePtr *patternLines;
    int patternLinesNum;
    bool advMode;
};

typedef PatternLines* patternLinesPtr;

#endif // PlayerPatternLines