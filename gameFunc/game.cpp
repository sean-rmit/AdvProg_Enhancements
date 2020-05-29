#include "game.h"

#include <iostream>
#include <string>
#include <exception>
#include <sstream>
#include <cstring>

Game::Game(int playersNum, int seed)
{
    factories = new Factories(playersNum);
    centre = new Centre;
    players = new Players(playersNum);
    lid = new Lid();
    bag = new Bag();
}
Game::~Game()
{
    delete factories;
    delete centre;
    delete players;
    delete lid;
    delete bag;
}

Game::Game(Game &other)
{
}

void Game::finaliseRound()
{
    for (int i = 0; i < players->getPlayersNum(); i++)
    {
        players->getPlayer(i)->addPenaltyPoints();
        players->getPlayer(i)->moveTilesFromPatternLineToWall(lid);
        players->getPlayer(i)->moveTilesFromBrokenTilesToLid(lid, centre);
    }
    if (centre->size() == 0)
    {
        centre->addTile(FIRSTPLAYER);
    }
}

void Game::prepareNewRound()
{
    // refill bag with tiles from lid if insufficient tiles
    if (bag->size() < 25)
    {
        int lidSize = lid->size();
        for (int i = 0; i < lidSize; i++)
        {
            bag->addTileToBack(lid->removeTileFront());
        }
    }
    for (int i = 0; i < factories->getFactoriesNum(); i++)
    {
        factories->getFactory(i)->loadFactory(bag);
    }
}

bool Game::playerMakesMove(int playerNum)
{
    int factoryNum;
    char tileColour;
    int patternlineIndex;
    std::string factoryNumAsString;
    std::cin >> factoryNumAsString;
    std::cin >> tileColour;
    std::string patternlineIndexAsString;
    std::cin >> patternlineIndexAsString;

    try
    {
        factoryNum = std::stoi(factoryNumAsString);
        patternlineIndex = std::stoi(patternlineIndexAsString);
    }
    catch (std::invalid_argument const &e)
    {
        std::cout << "Invalid input" << std::endl;
        return false;
    }
    catch (std::out_of_range const &e)
    {
        std::cout << "Integer overflow: std::out_of_range thrown" << std::endl;
        return false;
    }

    // validate factoryNum
    // factories->getFactoriesNum() + 1 because centre is included
    if (factoryNum < 0 || factoryNum >= factories->getFactoriesNum() + 1)
    {
        std::cout << "Invalid factoryNum!" << std::endl;
        return false;
    }

    //validate tileColour
    if (tileColour != RED && tileColour != YELLOW && tileColour != DARKBLUE && tileColour != LIGHTBLUE && tileColour != BLACK)
    {
        std::cout << "Invalid tileColour!" << std::endl;
        return false;
    }

    // validate patternlineIndex
    // PATTERN_LINES_NUM + 1 because broken line is included
    if (patternlineIndex < 1 || patternlineIndex > PATTERN_LINES_NUM + 1)
    {
        std::cout << "Invalid patternlineIndex!" << std::endl;
        return false;
    }
    bool validMove = false;
    // player move
    if (factoryNum == 0)
    {
        // patternlineIndex = 6 is broken line
        if (patternlineIndex == 6)
        {
            validMove = players->getPlayer(playerNum)->takeTilesFromCentreToBrokenLine(centre, tileColour, lid);
        }
        else
        {
            validMove = players->getPlayer(playerNum)->takeTilesFromCentre(tileColour, centre, patternlineIndex - 1, lid);
        }
        return validMove;
    }
    else
    {
        // patternlineIndex = 6 is broken line
        if (patternlineIndex == 6)
        {
            validMove = players->getPlayer(playerNum)->takeTilesFromFactoryToBrokenLine(factories->getFactory(factoryNum - 1), tileColour, centre, lid);
        }
        else
        {
            validMove = players->getPlayer(playerNum)->takeTilesFromFactory(factories->getFactory(factoryNum - 1), tileColour, centre, patternlineIndex - 1, lid);
        }
        return validMove;
    }
    std::cout << "DEBUG: end of playerMakesMove() function reached, this shouldn't happen" << std::endl;
    return false;
}

bool Game::hasRoundEnded()
{
    bool isEverythingEmpty = true;
    // check if centre is empty
    if (centre->size() != 0)
    {
        isEverythingEmpty = false;
    }
    // check if each factory is empty
    for (int i = 0; i < factories->getFactoriesNum(); i++)
    {
        if (factories->getFactory(i)->getLine()->getTilesNumber() != 0)
        {
            isEverythingEmpty = false;
        }
    }
    return isEverythingEmpty;
}

bool Game::hasGameEnded()
{
    for (int i = 0; i < WALL_LINES_NUM; i++)
    {
        for (int j = 0; j < players->getPlayersNum(); j++)
        {
            if (players->getPlayer(j)->getPlayerMosaic()->getPlayerWall()->getLine(i)->isFull())
            {
                return true;
            }
        }
    }
    return false;
}

void Game::finaliseGame()
{
    for (int i = 0; i < players->getPlayersNum(); i++)
    {
        players->getPlayer(i)->addEndGameBonusPoints();
    }
    std::cout << "Game has ended: " << std::endl;
    for (int i = 0; i < players->getPlayersNum(); i++)
    {
        std::cout << players->getPlayer(i)->getPlayerName() << "'s score: " << players->getPlayer(i)->getPlayerScore() << std::endl;
    }

    // TODO: tie feature
    int playerWithHighestScore = 0;
    int highestScore = 0;
    for (int i = 0; i < players->getPlayersNum(); i++)
    {
        if (players->getPlayer(i)->getPlayerScore() > highestScore) {
            highestScore = players->getPlayer(i)->getPlayerScore();
            playerWithHighestScore = i;
        }
    }
    std::cout << players->getPlayer(playerWithHighestScore)->getPlayerName() << " wins the game!" << std::endl;
}

// getters and setters
factoriesPtr Game::getFactories()
{
    return this->factories;
}

centrePtr Game::getCentre()
{
    return this->centre;
}

playersPtr Game::getPlayers() {
    return this->players;
}

playerPtr Game::getPlayer(int index)
{
    return this->players->getPlayer(index);
}

lidPtr Game::getLid()
{
    return this->lid;
}

bagPtr Game::getBag()
{
    return this->bag;
}