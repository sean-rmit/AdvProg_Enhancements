#include "PatternLines.h"
#include <iostream>
#include <string>
#include <exception>

PatternLines::PatternLines(bool advMode)
{
    this->advMode = advMode;
    if (advMode) {
        patternLinesNum = ADV_PATTERN_LINES_NUM;
    }
    else {
        patternLinesNum = NORMAL_PATTERN_LINES_NUM;
    }
    patternLines = new linePtr[patternLinesNum];
    for (int i = 0; i < patternLinesNum; i++)
    {
        Line *line = new Line(i + 1);
        patternLines[i] = line;
    }
}

PatternLines::~PatternLines()
{
    for (int i = 0; i < patternLinesNum; i++)
    {
        delete patternLines[i];
    }
    delete patternLines;
}

PatternLines::PatternLines(PatternLines &other) : PatternLines()
{
}

linePtr PatternLines::getLine(int index)
{
    try
    {
        if (index < 0 || index > patternLinesNum-1)
        {
            throw "Out of Bounds Exception!";
        }
    }
    catch (char const *e)
    {
        std::cout << "Error! Pattern Line has exceeded 5 lines! ";
        std::cout << e << std::endl;
    }
    return patternLines[index];
}
