#include <iostream>
#include <string>

#include "Player.h"

Player::Player(bool sixTileMode, bool greyMode)
{
    this->playerScore = 0;
    playerMosaic = new Mosaic(sixTileMode, greyMode);
}

Player::~Player()
{
    delete playerMosaic;
}

std::string Player::getPlayerName()
{
    return playerName;
}

void Player::setPlayerName(std::string name)
{
    this->playerName = name;
}

mosaicPtr Player::getPlayerMosaic()
{
    return playerMosaic;
}

void Player::setPlayerMosaic(Mosaic *mosaic)
{
    playerMosaic = mosaic;
}

int Player::getPlayerScore()
{
    return playerScore;
}

void Player::setPlayerScore(int score)
{
    playerScore = score;
}

void Player::addToPlayerScore(int score)
{
    playerScore += score;
}

bool Player::takeTilesFromFactory(Factory *factory, char colour, Centre *centre, int patternLineIndex, Lid *lid)
{
    bool tilesTaken = false;
    // if patternLine at patternLineIndex is already full, invalid move
    if (playerMosaic->getPlayerPatternLines()->getLine(patternLineIndex)->isFull())
    {
        std::cout << "Pattern line chosen is full!" << std::endl;
        return false;
    }
    // if factory is empty, invalid move
    else if (factory->getLine()->getTilesNumber() == 0)
    {
        std::cout << "Factory chosen is empty!" << std::endl;
        return false;
    }
    // if patternline chosen has a different colour, invalid move
    else if (playerMosaic->getPlayerPatternLines()->getLine(patternLineIndex)->getTileColour(0) != NOTILE && playerMosaic->getPlayerPatternLines()->getLine(patternLineIndex)->getTileColour(0) != colour)
    {
        std::cout << "Pattern line chosen already has the colour " << playerMosaic->getPlayerPatternLines()->getLine(patternLineIndex)->getTileColour(0) << ". Invalid move!" << std::endl;
    }
    // check if wall already has that colour
    for (int i = 0; i < playerMosaic->getPlayerWall()->getWallLinesNum(); i++)
    {
        if (playerMosaic->getPlayerWall()->getLine(patternLineIndex)->hasTile(i))
        {
            if (playerMosaic->getPlayerWall()->getLine(patternLineIndex)->getTileColour(i) == colour)
            {
                std::cout << "Wall already has that color on this line!" << std::endl;
                return false;
            }
        }
    }
    // check if factory contains the color specified first, if none then invalid move
    bool hasColour = false;
    for (int i = 0; i < factory->size(); i++)
    {
        // check if the factory has a tile in the current position i
        if (factory->getLine()->hasTile(i))
        {
            //check if the tile is the colour chosen by the player
            if (factory->getLine()->getTileColour(i) == colour)
            {
                hasColour = true;
            }
        }
    }
    if (!hasColour)
    {
        std::cout << "factory chosen does not have the colour " << colour << "!" << std::endl;
        return false;
    }

    for (int i = 0; i < factory->size(); i++)
    {
        // check if the factory has a tile in the current position i
        if (factory->getLine()->hasTile(i))
        {
            //check if the tile is the colour chosen by the player
            if (factory->getLine()->getTileColour(i) == colour)
            {
                //check if the player's pattern line still has space to put tiles
                if (!playerMosaic->getPlayerPatternLines()->getLine(patternLineIndex)->isFull())
                {
                    playerMosaic->putTileToPatternLine(factory->getLine()->removeTile(i), patternLineIndex);
                }
                //else if the pattern line is full, add it to player's broken tiles
                else
                {
                    // check if the player's broken tiles is full
                    if (!playerMosaic->getPlayerBrokenTiles()->getLine()->isFull())
                    {
                        playerMosaic->getPlayerBrokenTiles()->getLine()->addTileToBack(factory->getLine()->removeTile(i));
                    }
                    // else if broken tiles if full, add tile to lid
                    else
                    {
                        lid->addTileToBack(factory->getLine()->removeTile(i));
                    }
                }
                tilesTaken = true;
            }
            //else if tile is not the colour chosen by player, move it to the centre
            else
            {
                centre->addTile(factory->getLine()->removeTile(i));
            }
        }
        else
        {
            throw std::logic_error("Factory: Deleting on index with empty tile");
        }
    }
    return tilesTaken;
}

bool Player::takeTilesFromCentre(char colour, Centre *centre, int patternLineIndex, Lid *lid, bool &firstPlayerTokenTaken)
{
    bool tilesTaken = false;
    // if patternLine at patternLineIndex is already full, invalid move
    if (playerMosaic->getPlayerPatternLines()->getLine(patternLineIndex)->isFull())
    {
        std::cout << "Pattern line chosen is full!" << std::endl;
        return false;
    }
    // if patternline chosen has a different colour, invalid move
    else if (playerMosaic->getPlayerPatternLines()->getLine(patternLineIndex)->getTileColour(0) != NOTILE && playerMosaic->getPlayerPatternLines()->getLine(patternLineIndex)->getTileColour(0) != colour)
    {
        std::cout << "Pattern line chosen already has the colour " << playerMosaic->getPlayerPatternLines()->getLine(patternLineIndex)->getTileColour(0) << ". Invalid move!" << std::endl;
        return false;
    }
    // if patternLine at patternLineIndex is already full, invalid move
    if (playerMosaic->getPlayerPatternLines()->getLine(patternLineIndex)->isFull())
    {
        return false;
    }
    // check if centre contains the color specified first, if none then invalid move
    bool hasColour = false;
    for (int i = 0; i < centre->size(); i++)
    {
        //check if the tile is the colour chosen by the player
        if (centre->getTileColour(i) == colour)
        {
            hasColour = true;
        }
    }
    if (!hasColour)
    {
        std::cout << "centre does not have the colour " << colour << "!" << std::endl;
        return false;
    }

    int centreSize = centre->size();
    for (int i = 0; i < centreSize; i++)
    {
        // find the tiles from the centre according to the colour the player wants
        if (centre->getTileColour(i) == colour)
        {
            //check if the player's pattern line still has space to put tiles
            if (!playerMosaic->getPlayerPatternLines()->getLine(patternLineIndex)->isFull())
            {
                playerMosaic->putTileToPatternLine(centre->removeTile(i), patternLineIndex);
                i--;
                centreSize--;
            }

            //else if the pattern line is full, add it to player's broken tiles
            else
            {
                // check if the player's broken tiles is full
                if (!playerMosaic->getPlayerBrokenTiles()->getLine()->isFull())
                {
                    playerMosaic->getPlayerBrokenTiles()->getLine()->addTileToBack(centre->removeTile(i));
                    i--;
                    centreSize--;
                }
                // else if broken tiles if full, add tile to lid
                else
                {
                    lid->addTileToBack(centre->removeTile(i));
                    i--;
                    centreSize--;
                }
            }
            tilesTaken = true;
        }
    }
    // only take the Firstplayer token if at least one coloured tile was taken from the centre,
    // else it was a invalid move and player should repeat his turn again
    // also does not take the Firstplayer token if the player's brokenline is full
    // for 1-centre game
    if (tilesTaken && !playerMosaic->getPlayerBrokenTiles()->getLine()->isFull() && centre->size() > 0 && centre->getTileColour(0) == FIRSTPLAYER)
    {
        // check if the player's broken tiles is full
        if (!playerMosaic->getPlayerBrokenTiles()->getLine()->isFull())
        {
            playerMosaic->getPlayerBrokenTiles()->getLine()->addTileToBack(centre->removeTile(0));
        }
        else
        {
            // remove the F token anyway if the player is suppose to take it but couldn't due to a full
            // broken line, if this happens the firstplayer next round will be the player who started
            // this round
            centre->removeTile(0);
        }
        firstPlayerTokenTaken = true;
    }
    // for 2-centre game
    if (tilesTaken && !playerMosaic->getPlayerBrokenTiles()->getLine()->isFull() && !firstPlayerTokenTaken)
    {
        playerMosaic->getPlayerBrokenTiles()->getLine()->addTileToBack(FIRSTPLAYER);
        firstPlayerTokenTaken = true;
    }
    return tilesTaken;
}

bool Player::takeTilesFromFactoryToBrokenLine(Factory *factory, char colour, Centre *centre, Lid *lid)
{
    bool tilesTaken = false;
    // if factory is empty, invalid move
    if (factory->getLine()->getTilesNumber() == 0)
    {
        std::cout << "Factory chosen is empty!" << std::endl;
        return false;
    }
    // check if factory contains the color specified first, if none then invalid move
    bool hasColour = false;
    for (int i = 0; i < factory->size(); i++)
    {
        // check if the factory has a tile in the current position i
        if (factory->getLine()->hasTile(i))
        {
            //check if the tile is the colour chosen by the player
            if (factory->getLine()->getTileColour(i) == colour)
            {
                hasColour = true;
            }
        }
    }
    if (!hasColour)
    {
        std::cout << "factory chosen does not have the colour " << colour << "!" << std::endl;
        return false;
    }
    for (int i = 0; i < factory->size(); i++)
    {
        // check if the factory has a tile in the current position i
        if (factory->getLine()->hasTile(i))
        {
            //check if the tile is the colour chosen by the player
            if (factory->getLine()->getTileColour(i) == colour)
            {
                // check if the player's broken tiles is full
                if (!playerMosaic->getPlayerBrokenTiles()->getLine()->isFull())
                {
                    playerMosaic->getPlayerBrokenTiles()->getLine()->addTileToBack(factory->getLine()->removeTile(i));
                }
                // else if broken tiles if full, add tile to lid
                else
                {
                    lid->addTileToBack(factory->getLine()->removeTile(i));
                }
                tilesTaken = true;
            }
            //else if tile is not the colour chosen by player, move it to the centre
            else
            {
                centre->addTile(factory->getLine()->removeTile(i));
            }
        }
        else
        {
            throw std::logic_error("Factory: Deleting on index with empty tile");
        }
    }
    return tilesTaken;
}

bool Player::takeTilesFromCentreToBrokenLine(Centre *centre, char colour, Lid *lid, bool &firstPlayerTokenTaken)
{
    bool tilesTaken = false;
    // check if centre contains the color specified first, if none then invalid move
    bool hasColour = false;
    for (int i = 0; i < centre->size(); i++)
    {
        //check if the tile is the colour chosen by the player
        if (centre->getTileColour(i) == colour)
        {
            hasColour = true;
        }
    }
    if (!hasColour)
    {
        std::cout << "centre does not have the colour " << colour << "!" << std::endl;
        return false;
    }

    int centreSize = centre->size();
    for (int i = 0; i < centreSize; i++)
    {
        // find the tiles from the centre according to the colour the player wants
        if (centre->getTileColour(i) == colour)
        {
            // check if the player's broken tiles is full
            if (!playerMosaic->getPlayerBrokenTiles()->getLine()->isFull())
            {
                playerMosaic->getPlayerBrokenTiles()->getLine()->addTileToBack(centre->removeTile(i));
                i--;
                centreSize--;
            }
            // else if broken tiles if full, add tile to lid
            else
            {
                lid->addTileToBack(centre->removeTile(i));
                i--;
                centreSize--;
            }
            tilesTaken = true;
        }
    }
    // only take the Firstplayer token if at least one coloured tile was taken from the centre,
    // else it was a invalid move and player should repeat his turn again
    // Firstplayer token also does not get taken if the player's brokenline is full
    // for 1-centre game
    if (tilesTaken && !playerMosaic->getPlayerBrokenTiles()->getLine()->isFull() && centre->size() > 0 && centre->getTileColour(0) == FIRSTPLAYER)
    {
        // check if the player's broken tiles is full
        if (!playerMosaic->getPlayerBrokenTiles()->getLine()->isFull())
        {
            playerMosaic->getPlayerBrokenTiles()->getLine()->addTileToBack(centre->removeTile(0));
        }
        else
        {
            // remove the F token anyway if the player is suppose to take it but couldn't due to a full
            // broken line, if this happens the firstplayer next round will be the player who started
            // this round
            centre->removeTile(0);
        }
        firstPlayerTokenTaken = true;
    }
    // for 2-centre game
    if (tilesTaken && !playerMosaic->getPlayerBrokenTiles()->getLine()->isFull() && !firstPlayerTokenTaken)
    {
        playerMosaic->getPlayerBrokenTiles()->getLine()->addTileToBack(FIRSTPLAYER);
        firstPlayerTokenTaken = true;
    }
    return tilesTaken;
}

void Player::moveTilesFromPatternLineToWall(Lid *lid, bool greyMode)
{
    if (!greyMode)
    {
        for (int lineIndex = 0; lineIndex < playerMosaic->getPlayerPatternLines()->getPatternLinesNum(); lineIndex++)
        {
            if (playerMosaic->getPlayerPatternLines()->getLine(lineIndex)->isFull())
            {
                for (int i = 0; i < playerMosaic->getPlayerPatternLines()->getLine(lineIndex)->size(); i++)
                {
                    int points = playerMosaic->getPlayerWall()->addTile(playerMosaic->getPlayerPatternLines()->getLine(lineIndex)->removeTile(i), lineIndex, lid);
                    addToPlayerScore(points);
                }
            }
        }
    }
    // Wall tilting phase for grey mode
    else
    {
        bool tiltingInstructions = true;
        for (int lineIndex = 0; lineIndex < playerMosaic->getPlayerPatternLines()->getPatternLinesNum(); lineIndex++)
        {
            if (playerMosaic->getPlayerPatternLines()->getLine(lineIndex)->isFull())
            {
                printGreyModeTiltingUI(lineIndex, tiltingInstructions);
                tiltingInstructions = false;
                bool columnChosen = false;
                std::string wallColumnAsString;
                int wallColumn = 0;
                // TODO: check for EOF, more checks are needed (already has tile, check vertical)
                while (!columnChosen)
                {
                    std::cout << "Wall Column:" << std::endl;
                    std::cout << ">";
                    std::cin >> wallColumnAsString;
                    std::cout << std::endl;
                    if (std::cin.eof())
                    {
                        columnChosen = true;
                    }
                    else
                    {
                        try
                        {
                            wallColumn = std::stoi(wallColumnAsString);
                            columnChosen = true;
                            wallColumn--;
                        }
                        catch (std::invalid_argument const &e)
                        {
                            std::cout << "Invalid input. Please try again." << std::endl;
                        }
                        catch (std::out_of_range const &e)
                        {
                            std::cout << "Integer overflow: std::out_of_range thrown" << std::endl;
                        }
                        if (columnChosen)
                        {
                            // check if the wall column index chosen is valid
                            if (wallColumn >= 0 && wallColumn < playerMosaic->getPlayerWall()->getWallLinesNum())
                            {
                                // next check if the wall column index does not already has a value
                                if (!playerMosaic->getPlayerWall()->getLine(lineIndex)->hasTile(wallColumn))
                                {
                                    // next check if the vertical column has a duplicate color
                                    bool duplicate = false;
                                    for (int i = 0; i < playerMosaic->getPlayerWall()->getWallLinesNum(); i++)
                                    {
                                        if (playerMosaic->getPlayerWall()->getLine(i)->getTileColour(wallColumn) == playerMosaic->getPlayerPatternLines()->getLine(lineIndex)->getTileColour(0))
                                        {
                                            duplicate = true;
                                        }
                                    }
                                    if (!duplicate)
                                    {
                                        columnChosen = true;
                                    }
                                    else
                                    {
                                        std::cout << "Wall column index chosen already has a tile of the same color on the vertical axis. Please try again." << std::endl;
                                        columnChosen = false;
                                    }
                                }
                                else
                                {
                                    std::cout << "Wall column index chosen already has a tile. Please try again." << std::endl;
                                    columnChosen = false;
                                }
                            }
                            else
                            {
                                std::cout << "Invalid Wall column chosen. Please try again." << std::endl;
                                columnChosen = false;
                            }
                        }
                    }
                }

                for (int i = 0; i < playerMosaic->getPlayerPatternLines()->getLine(lineIndex)->size(); i++)
                {
                    int points = playerMosaic->getPlayerWall()->addTileGreyMode(playerMosaic->getPlayerPatternLines()->getLine(lineIndex)->removeTile(i), lineIndex, wallColumn, lid);
                    addToPlayerScore(points);
                }
            }
        }
    }
}

void Player::moveTilesFromBrokenTilesToLid(Lid *lid)
{
    playerMosaic->getPlayerBrokenTiles()->moveAllTilesToLid(lid);
}

void Player::addPenaltyPoints()
{
    addToPlayerScore(playerMosaic->getPlayerBrokenTiles()->getPenaltyPoints());
}

void Player::addEndGameBonusPoints()
{
    addToPlayerScore(playerMosaic->getPlayerWall()->addEndGameBonusPoints());
}

void Player::printGreyModeTiltingUI(int patternLineIndex, bool instructions)
{
    if (instructions)
    {
        std::cout << "=======================================" << std::endl;
        std::cout << "Wall Tilting Phase - Player: " << playerName << std::endl;
        std::cout << "Choose the column index (1-" << playerMosaic->getPlayerWall()->getWallLinesNum() << ") of your wall you would like to place your tile" << std::endl;
        std::cout << "for the targeted line index with symbol '>>'" << std::endl;
        std::cout << "=======================================" << std::endl;
    }
    std::cout << "Column Index:";
    for (int i = 0; i < playerMosaic->getPlayerPatternLines()->getPatternLinesNum() - 3; i++)
    {
        std::cout << " ";
    }

    for (int i = 0; i < playerMosaic->getPlayerWall()->getWallLinesNum(); i++)
    {
        std::cout << i + 1;
    }
    std::cout << std::endl;
    for (int i = 0; i < playerMosaic->getPlayerPatternLines()->getPatternLinesNum(); i++)
    {
        if (i == patternLineIndex)
        {
            std::cout << ">>";
        }
        else
        {
            std::cout << "  ";
        }
        std::cout << i + 1 << ": ";
        for (int j = 0; j < playerMosaic->getPlayerPatternLines()->getPatternLinesNum() - i; j++)
        {
            std::cout << " ";
        }
        std::cout << playerMosaic->getPlayerPatternLines()->getLine(i)->getTilesAsString(true, true);
        std::cout << " || ";
        std::cout << playerMosaic->getPlayerWall()->getLine(i)->getTilesAsString(true, true) << std::endl;
    }
}
