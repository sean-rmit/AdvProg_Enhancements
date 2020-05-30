#include <iostream>
#include <sstream>
#include <cstring>

#include "utils.h"

void printString(std::string s, int num)
{
    for (int i = 0; i < num; i++)
    {
        std::cout << s;
    }
}

void printFactories(Factories *factories)
{
    std::cout << "Factories:" << std::endl;
    printString("=", 15);
    std::cout << std::endl;
    for (int i = 0; i < factories->getCentresNum(); i++)
    {
        std::cout << i << " - Centre: " << factories->getCentre(i)->getTilesAsString() << std::endl;
    }
    for (int i = 0; i < factories->getFactoriesNum(); i++)
    {
        std::cout << i + factories->getCentresNum() << " - Factory: " << factories->getFactory(i)->getLine()->getTilesAsString(false) << std::endl;
    }
    printString("=", 15);
}

void printPlayerMosaic(Player *player)
{
    std::cout << "Mosaic for " << player->getPlayerName() << " :" << std::endl;
    for (int i = 0; i < PATTERN_LINES_NUM; i++)
    {
        std::cout << i + 1 << ": ";
        for (int j = 0; j < PATTERN_LINES_NUM - i; j++)
        {
            std::cout << " ";
        }
        std::cout << player->getPlayerMosaic()->getPlayerPatternLines()->getLine(i)->getTilesAsString(true);
        std::cout << " || ";
        std::cout << player->getPlayerMosaic()->getPlayerWall()->getLine(i)->getTilesAsString(true) << std::endl;
    }
    std::cout << "6: broken: " << player->getPlayerMosaic()->getPlayerBrokenTiles()->getLine()->getTilesAsString(true) << std::endl;
}

void printPlayerMosaics(Players *players)
{
    std::cout << "Mosaics of Players:" << std::endl;
    // print player names
    for (int playerNum = 0; playerNum < players->getPlayersNum(); playerNum++)
    {
        std::string playerName = players->getPlayer(playerNum)->getPlayerName();
        std::cout << playerName << ":";
        int spacesNeeded = PLAYER_MOSAIC_CONSTRAINT_ON_CONSOLE - playerName.size();
        printString(" ", spacesNeeded);
    }
    std::cout << std::endl;

    // print players mosaic lines
    int spacesNeeded = GAP_SIZE;
    for (int i = 0; i < PATTERN_LINES_NUM; i++)
    {
        for (int playerNum = 0; playerNum < players->getPlayersNum(); playerNum++)
        {
            std::cout << i + 1 << ": ";
            for (int j = 0; j < PATTERN_LINES_NUM - i; j++)
            {
                std::cout << " ";
            }
            std::cout << players->getPlayer(playerNum)->getPlayerMosaic()->getPlayerPatternLines()->getLine(i)->getTilesAsString(true);
            std::cout << " || ";
            std::cout << players->getPlayer(playerNum)->getPlayerMosaic()->getPlayerWall()->getLine(i)->getTilesAsString(true);
            printString(" ", spacesNeeded);
        }
        std::cout << std::endl;
    }
    for (int playerNum = 0; playerNum < players->getPlayersNum(); playerNum++)
    {
        std::cout << "6: broken: " << players->getPlayer(playerNum)->getPlayerMosaic()->getPlayerBrokenTiles()->getLine()->getTilesAsString(true);
        printString(" ", spacesNeeded);
    }
    std::cout << std::endl;
}

void printPlayerPoints(Players *players)
{
    for (int i = 0; i < players->getPlayersNum(); i++)
    {
        std::cout << players->getPlayer(i)->getPlayerName() << "'s score: " << players->getPlayer(i)->getPlayerScore() << std::endl;
    }
}
