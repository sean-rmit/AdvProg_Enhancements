#include "game.h"

#include <iostream>
#include <string>
#include <exception>
#include <sstream>
#include <cstring>

Game::Game()
{
    lid = new Lid();
    bag = new Bag();
    twoCentres = false;
    firstplayerTokenTaken = false;
    greyMode = false;
    sixTileMode = false;
}

Game::Game(int playersNum, int centresNum, bool sixTileMode, bool greyMode, int seed)
{
    this->sixTileMode = sixTileMode;
    this->greyMode = greyMode;
    factories = new Factories(playersNum, centresNum);
    players = new Players(playersNum, sixTileMode, greyMode);
    lid = new Lid();
    bag = new Bag();
    twoCentres = false;
    firstplayerTokenTaken = false;
    if (centresNum == 2)
    {
        twoCentres = true;
    }
}
Game::~Game()
{
    delete factories;
    delete players;
    delete lid;
    delete bag;
}

Game::Game(Game &other)
{
}

void Game::createFactoriesAndPlayers(int playersNum, int centresNum, bool sixTileMode, bool greyMode)
{
    factories = new Factories(playersNum, centresNum);
    players = new Players(playersNum, sixTileMode, greyMode);
    if (centresNum == 2)
    {
        twoCentres = true;
    }
    this->sixTileMode = sixTileMode;
    this->greyMode = greyMode;
}

void Game::finaliseRound()
{
    for (int i = 0; i < players->getPlayersNum(); i++)
    {
        players->getPlayer(i)->addPenaltyPoints();
        players->getPlayer(i)->moveTilesFromPatternLineToWall(lid, greyMode);
        players->getPlayer(i)->moveTilesFromBrokenTilesToLid(lid);
    }
    // 1 centre mode needs to manage Firstplayer token in it
    if (factories->getCentresNum() == 1 && factories->getCentre(0)->size() == 0)
    {
        factories->getCentre(0)->addTile(FIRSTPLAYER);
    }
    firstplayerTokenTaken = false;
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

bool Game::determineFirstPlayer(int &turnCounter)
{
    for (int i = 0; i < players->getPlayersNum(); i++)
    {
        for (int j = 0; j < players->getPlayer(i)->getPlayerMosaic()->getPlayerBrokenTiles()->getLine()->size(); j++)
        {
            if (players->getPlayer(i)->getPlayerMosaic()->getPlayerBrokenTiles()->getLine()->getTileColour(j) == FIRSTPLAYER)
            {
                turnCounter = i;
                std::cout << "Player with Firstplayer token: " << players->getPlayer(i)->getPlayerName() << std::endl;
                return true;
            }
        }
    }
    return false;
}

bool Game::playerMakesMove(int playerNum)
{
    int factoryNum;
    char tileColour;
    int patternlineIndex;
    int targetCentre = 0;
    std::string factoryNumAsString;
    std::cin >> factoryNumAsString;
    std::cin >> tileColour;
    std::string patternlineIndexAsString;
    std::cin >> patternlineIndexAsString;
    std::string targetCentreAsString;

    // parsing the inputs into desirable variable types
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
    if (twoCentres && factoryNum > 1)
    {
        std::cout << "Select a centre to put your excess tiles:" << std::endl;
        std::cout << ">";
        std::cin >> targetCentreAsString;
        try
        {
            targetCentre = std::stoi(targetCentreAsString);
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
    }

    // validate factoryNum
    if (factoryNum < 0 || factoryNum >= factories->getFactoriesNum() + factories->getCentresNum())
    {
        std::cout << "Invalid factoryNum!" << std::endl;
        return false;
    }

    //validate tileColour
    if (tileColour != RED && tileColour != YELLOW && tileColour != DARKBLUE && tileColour != LIGHTBLUE && tileColour != BLACK)
    {
        if (sixTileMode && tileColour == ORANGE) {
            
        }
        else {
            std::cout << "Invalid tileColour!" << std::endl;
            return false;
        }
    }

    // validate patternlineIndex
    // PATTERN_LINES_NUM + 1 because broken line is included
    if (patternlineIndex < 1 || patternlineIndex > players->getPlayer(playerNum)->getPlayerMosaic()->getPlayerPatternLines()->getPatternLinesNum() + 1)
    {
        std::cout << "Invalid patternlineIndex!" << std::endl;
        return false;
    }

    // validate targetCentre
    if (twoCentres && (targetCentre < 0 || targetCentre > 1))
    {
        std::cout << "Invalid target Centre!" << std::endl;
        return false;
    }

    bool validMove = false;
    // player move
    // if there are 2 centres, factory 0 & 1 are centres, factory 2 onwards is only an actual facory
    if (twoCentres)
    {
        if (factoryNum == 0 || factoryNum == 1)
        {
            // total pattern lines + 1 is broken line
            if (patternlineIndex == players->getPlayer(playerNum)->getPlayerMosaic()->getPlayerPatternLines()->getPatternLinesNum() + 1)
            {
                validMove = players->getPlayer(playerNum)->takeTilesFromCentreToBrokenLine(factories->getCentre(factoryNum), tileColour, lid, firstplayerTokenTaken);
            }
            else
            {
                validMove = players->getPlayer(playerNum)->takeTilesFromCentre(tileColour, factories->getCentre(factoryNum), patternlineIndex - 1, lid, firstplayerTokenTaken);
            }
            return validMove;
        }
        else
        {
            // total pattern lines + 1 is broken line
            // factoryNum - 2 to remove the 2 centres at the front
            if (patternlineIndex == players->getPlayer(playerNum)->getPlayerMosaic()->getPlayerPatternLines()->getPatternLinesNum() + 1)
            {
                validMove = players->getPlayer(playerNum)->takeTilesFromFactoryToBrokenLine(factories->getFactory(factoryNum - 2), tileColour, factories->getCentre(targetCentre), lid);
            }
            else
            {
                validMove = players->getPlayer(playerNum)->takeTilesFromFactory(factories->getFactory(factoryNum - 2), tileColour, factories->getCentre(targetCentre), patternlineIndex - 1, lid);
            }
            return validMove;
        }
    }
    // if there is only 1 centre
    else
    {
        if (factoryNum == 0)
        {
            // total pattern lines + 1 is broken line
            if (patternlineIndex == players->getPlayer(playerNum)->getPlayerMosaic()->getPlayerPatternLines()->getPatternLinesNum() + 1)
            {
                validMove = players->getPlayer(playerNum)->takeTilesFromCentreToBrokenLine(factories->getCentre(targetCentre), tileColour, lid, firstplayerTokenTaken);
            }
            else
            {
                validMove = players->getPlayer(playerNum)->takeTilesFromCentre(tileColour, factories->getCentre(targetCentre), patternlineIndex - 1, lid, firstplayerTokenTaken);
            }
            return validMove;
        }
        else
        {
            // total pattern lines + 1 is broken line
            // factoryNum - 1 to remove the 1 centre at the front
            if (patternlineIndex == players->getPlayer(playerNum)->getPlayerMosaic()->getPlayerPatternLines()->getPatternLinesNum() + 1)
            {
                validMove = players->getPlayer(playerNum)->takeTilesFromFactoryToBrokenLine(factories->getFactory(factoryNum - 1), tileColour, factories->getCentre(targetCentre), lid);
            }
            else
            {
                validMove = players->getPlayer(playerNum)->takeTilesFromFactory(factories->getFactory(factoryNum - 1), tileColour, factories->getCentre(targetCentre), patternlineIndex - 1, lid);
            }
            return validMove;
        }
    }
    return false;
}

bool Game::hasRoundEnded()
{
    bool isEverythingEmpty = true;
    // check if centre is empty
    for (int i = 0; i < factories->getCentresNum(); i++)
    {
        if (factories->getCentre(i)->size() != 0)
        {
            isEverythingEmpty = false;
        }
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
    for (int i = 0; i < players->getPlayer(0)->getPlayerMosaic()->getPlayerWall()->getWallLinesNum(); i++)
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
    std::cout << "Scores:" << std::endl;
    for (int i = 0; i < players->getPlayersNum(); i++)
    {
        std::cout << players->getPlayer(i)->getPlayerName() << "'s score: " << players->getPlayer(i)->getPlayerScore() << std::endl;
    }
    std::cout << std::endl;

    // A vector of players with highest score as there might be a tie
    std::vector<int> playerWithHighestScore;
    int highestScore = 0;
    for (int i = 0; i < players->getPlayersNum(); i++)
    {
        // if the iterated player's score exceeded the previous highest
        if (players->getPlayer(i)->getPlayerScore() > highestScore)
        {
            highestScore = players->getPlayer(i)->getPlayerScore();
            playerWithHighestScore.clear();
            playerWithHighestScore.push_back(i);
        }
        // if the iterated player's score is the same as the previous highest
        else if (players->getPlayer(i)->getPlayerScore() == highestScore)
        {
            playerWithHighestScore.push_back(i);
        }
    }
    std::cout << "The following player(s) has won the game: " << std::endl;
    for (int i = 0; i < (int)playerWithHighestScore.size(); i++)
    {
        std::cout << i + 1 << ". " << players->getPlayer(playerWithHighestScore.at(i))->getPlayerName() << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Congratulations!!!" << std::endl;
    std::cout << std::endl;
}

// getters and setters
void Game::setFirstPlayerTokenTaken(bool taken) {
    this->firstplayerTokenTaken = taken;
}

factoriesPtr Game::getFactories()
{
    return this->factories;
}

playersPtr Game::getPlayers()
{
    return this->players;
}

lidPtr Game::getLid()
{
    return this->lid;
}

bagPtr Game::getBag()
{
    return this->bag;
}

bool Game::isSixTileMode()
{
    return this->sixTileMode;
}

bool Game::isGreyMode()
{
    return this->greyMode;
}

bool Game::isFirstPlayerTokenTaken() {
    return this->firstplayerTokenTaken;
}