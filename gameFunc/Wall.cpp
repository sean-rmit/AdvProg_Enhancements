#include "Wall.h"

Wall::Wall(bool advMode, bool greyMode)
{
    this->advMode = advMode;
    this->greyMode = greyMode;
    if (!advMode)
    {
        wallLinesNum = NORMAL_WALL_LINES_NUM;
    }
    else
    {
        wallLinesNum = ADV_WALL_LINES_NUM;
    }
    wallLines = new linePtr[wallLinesNum];
    for (int i = 0; i < wallLinesNum; i++)
    {
        Line *line = new Line(wallLinesNum);
        wallLines[i] = line;
    }
    if (!greyMode)
    {
        initialiseFixedColourPattern();
    }
}

Wall::~Wall()
{
    for (int i = 0; i < wallLinesNum; i++)
    {
        delete wallLines[i];
    }
    delete wallLines;
}

Wall::Wall(Wall &other)
{
}

void Wall::initialiseFixedColourPattern()
{
    // read in from an fixedWallPatternTiles.txt file
    std::string filename;
    if (advMode)
    {
        filename = "fixedWallPatternTilesAdv.txt";
    }
    else
    {
        filename = "fixedWallPatternTiles.txt";
    }

    std::ifstream inputFile(filename);
    for (int i = 0; i < wallLinesNum; i++)
    {
        for (int j = 0; j < wallLinesNum; j++)
        {
            inputFile >> fixedColourPattern[i][j];
        }
    }
}

int Wall::getWallLinesNum()
{
    return this->wallLinesNum;
}

linePtr Wall::getLine(int index)
{
    return wallLines[index];
}

int Wall::addTile(char tile, int lineIndex, Lid *lid)
{
    int points = 0;
    for (int i = 0; i < wallLinesNum; i++)
    {
        if (fixedColourPattern[lineIndex][i] == tile)
        {
            if (!wallLines[lineIndex]->hasTile(i))
            {
                wallLines[lineIndex]->addTileToIndex(tile, i);

                // scoring implementation
                int adjacentTilesOnRow = 0;
                int adjacentTilesOnCol = 0;
                int row = lineIndex;
                int col = i;

                // check row
                while (col + 1 < wallLinesNum && wallLines[row]->hasTile(col + 1))
                {
                    adjacentTilesOnRow++;
                    col++;
                }
                col = i;
                while (col - 1 >= 0 && wallLines[row]->hasTile(col - 1))
                {
                    adjacentTilesOnRow++;
                    col--;
                }
                col = i;
                // check column
                while (row + 1 < wallLinesNum && wallLines[row + 1]->hasTile(col))
                {
                    adjacentTilesOnCol++;
                    row++;
                }
                row = lineIndex;
                while (row - 1 >= 0 && wallLines[row - 1]->hasTile(col))
                {
                    adjacentTilesOnCol++;
                    row--;
                }
                if (adjacentTilesOnRow != 0)
                {
                    points += adjacentTilesOnRow + 1;
                }
                if (adjacentTilesOnCol != 0)
                {
                    points += adjacentTilesOnCol + 1;
                }
                if (adjacentTilesOnCol == 0 && adjacentTilesOnRow == 0)
                {
                    points = 1;
                }
                // end of scoring implementation
            }
            else
            {
                lid->addTileToBack(tile);
            }
        }
    }
    return points;
}

int Wall::addTileGreyMode(char tile, int lineIndex, int wallColumn, Lid *lid)
{
    int points = 0;
    if (!wallLines[lineIndex]->hasTile(wallColumn))
    {
        wallLines[lineIndex]->addTileToIndex(tile, wallColumn);

        // scoring implementation
        int adjacentTilesOnRow = 0;
        int adjacentTilesOnCol = 0;
        int row = lineIndex;
        int col = wallColumn;

        // check row
        while (col + 1 < wallLinesNum && wallLines[row]->hasTile(col + 1))
        {
            adjacentTilesOnRow++;
            col++;
        }
        col = wallColumn;
        while (col - 1 >= 0 && wallLines[row]->hasTile(col - 1))
        {
            adjacentTilesOnRow++;
            col--;
        }
        col = wallColumn;
        // check column
        while (row + 1 < wallLinesNum && wallLines[row + 1]->hasTile(col))
        {
            adjacentTilesOnCol++;
            row++;
        }
        row = lineIndex;
        while (row - 1 >= 0 && wallLines[row - 1]->hasTile(col))
        {
            adjacentTilesOnCol++;
            row--;
        }
        if (adjacentTilesOnRow != 0)
        {
            points += adjacentTilesOnRow + 1;
        }
        if (adjacentTilesOnCol != 0)
        {
            points += adjacentTilesOnCol + 1;
        }
        if (adjacentTilesOnCol == 0 && adjacentTilesOnRow == 0)
        {
            points = 1;
        }
        // end of scoring implementation
    }
    else
    {
        lid->addTileToBack(tile);
    }
    return points;
}

int Wall::addEndGameBonusPoints()
{
    int points = 0;
    int completedRows = 0;
    int completedCols = 0;
    int completedColours = 0;

    // count completed rows
    for (int rowIndex = 0; rowIndex < wallLinesNum; rowIndex++)
    {
        if (wallLines[rowIndex]->isFull())
        {
            completedRows++;
        }
    }

    // count completed columns
    for (int colIndex = 0; colIndex < wallLinesNum; colIndex++)
    {
        int counter = 0;
        for (int rowIndex = 0; rowIndex < wallLinesNum; rowIndex++)
        {
            if (wallLines[rowIndex]->hasTile(colIndex))
            {
                counter++;
            }
        }
        if (counter == wallLinesNum)
        {
            completedCols++;
        }
        counter = 0;
    }

    // count complete colours
    char tile;
    int red = 0, yellow = 0, lightBlue = 0, darkBlue = 0, black = 0, orange = 0;
    for (int rowIndex = 0; rowIndex < wallLinesNum; rowIndex++)
    {
        for (int colIndex = 0; colIndex < wallLinesNum; colIndex++)
        {
            tile = wallLines[rowIndex]->getTileColour(colIndex);
            if (tile == RED)
            {
                red++;
            }
            else if (tile == YELLOW)
            {
                yellow++;
            }
            else if (tile == LIGHTBLUE)
            {
                lightBlue++;
            }
            else if (tile == DARKBLUE)
            {
                darkBlue++;
            }
            else if (tile == BLACK)
            {
                black++;
            }
            else if (tile == ORANGE)
            {
                orange++;
            }
        }
    }
    if (red == wallLinesNum)
    {
        completedColours++;
    }
    if (yellow == wallLinesNum)
    {
        completedColours++;
    }
    if (black == wallLinesNum)
    {
        completedColours++;
    }
    if (darkBlue == wallLinesNum)
    {
        completedColours++;
    }
    if (lightBlue == wallLinesNum)
    {
        completedColours++;
    }
    if (orange == wallLinesNum)
    {
        completedColours++;
    }

    // calculate bonus points
    points += (completedRows * 2) + (completedCols * 7) + (completedColours * 10);
    return points;
}