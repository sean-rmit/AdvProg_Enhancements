#ifndef MosaicWall
#define MosaicWall

#include "Line.h"
#include "PatternLines.h"
#include "BoxLid.h"

#include <iostream>
#include <fstream>

#define NORMAL_WALL_LINES_NUM 5
#define ADV_WALL_LINES_NUM    6

class Wall {
public:

    Wall(bool advMode, bool greyMode);
    ~Wall();

    // copy constructor
    Wall(Wall& other);
    
    void initialiseFixedColourPattern();

    // getter for wallLinesNum
    int getWallLinesNum();

    // get line object at given index
    linePtr getLine(int index);
    // Gets tile and puts it in the the wall at set index
    int addTile(char tile, int lineIndex, Lid *lid);
    // Gets tile and puts it in the the wall at the given index for grey mode
    int addTileGreyMode(char tile, int lineIndex, int wallColumn, Lid *lid);
    
    // Calculates bonus points for the player
    int addEndGameBonusPoints();

private:
    linePtr *wallLines;
    char fixedColourPattern[NORMAL_WALL_LINES_NUM][NORMAL_WALL_LINES_NUM];
    int wallLinesNum;
    bool advMode;
    bool greyMode;
};

typedef Wall* wallPtr;

#endif // MosaicWall