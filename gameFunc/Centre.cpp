#include "Centre.h"

#include <iostream>

Centre::Centre() : centreTiles()
{
}

Centre::Centre(Centre &other)
{
}

Centre::~Centre()
{
    clear();
}

int Centre::size()
{
    return (int)centreTiles.size();
}

void Centre::addTile(char tileP)
{
    centreTiles.push_back(tileP);
}

char Centre::getTileColour(int index)
{
    return centreTiles.at(index);
}

char Centre::removeTile(int index)
{
    if ((unsigned int)index < centreTiles.size())
    {
        char tile = centreTiles.at(index);
        centreTiles.erase(centreTiles.begin() + index);
        return tile;
    }
    else
    {
        throw std::logic_error("ERROR: index out of bounds of centre's vector range");
    }
}

void Centre::clear()
{
    centreTiles.clear();
}

std::string Centre::getTilesAsString(bool painted)
{
    std::string allTilesAsString;
    Painter *painter = new Painter();
    for (unsigned int i = 0; i < centreTiles.size(); i++)
    {
        if (painted) {
            char tile = centreTiles.at(i);
            allTilesAsString += painter->paintTile(tile);
        }
        else {
            allTilesAsString += centreTiles.at(i);
        }
    }
    return allTilesAsString;
}