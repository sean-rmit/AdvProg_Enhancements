#ifndef MosaicWall
#define MosaicWall

#include "Line.h"
#include "PatternLines.h"
#include "BoxLid.h"

#include <iostream>
#include <string>
#include <fstream>

#define NORMAL_WALL_LINES_NUM 5
#define SIX_TILE_MODE_WALL_LINES_NUM    6

class Wall {
public:

    Wall(bool sixTileMode, bool greyMode);
    ~Wall();

    // copy constructor
    Wall(Wall& other);
    
    void initialiseFixedColourPattern();

    // getter for wallLinesNum
    int getWallLinesNum();

    std::string getTilesAsStringFixedWallMode(int lineIndex);

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
    // char fixedColourPattern[NORMAL_WALL_LINES_NUM][NORMAL_WALL_LINES_NUM];
    linePtr *fixedColourPattern; // the wall template on a fixed wall colour game
    int wallLinesNum;
    bool sixTileMode;
    bool greyMode;
};

typedef Wall* wallPtr;

#endif // MosaicWall