#include <fstream>
#include <iostream>
#include <string>
#include "LoadSaveFile.h"

LoadSave::LoadSave()
{
}

LoadSave::~LoadSave()
{
}

LoadSave::LoadSave(LoadSave &other)
{
}

void LoadSave::saveFile(std::string saveFile, Game *game, int currentPlayer)
{
    std::ofstream saveToFile(saveFile);

    // Advanced mode and Grey mode
    saveToFile << "ADV_MODE=" << game->isAdvMode() << std::endl;
    saveToFile << "GREY_MODE=" << game->isGreyMode() << std::endl;

    // Number of players
    saveToFile << "NUMBER_OF_PLAYERS=" << game->getPlayers()->getPlayersNum() << std::endl;

    // Number of centres
    saveToFile << "NUMBER_OF_CENTRES=" << game->getFactories()->getCentresNum() << std::endl;

    // Bag
    saveToFile << "BAG=" << game->getBag()->getTilesAsString() << std::endl;

    // Lid
    saveToFile << "LID=" << game->getLid()->getTilesAsString() << std::endl;

    // Factory Details
    for (int i = 0; i < game->getFactories()->getCentresNum(); i++)
    {
        saveToFile << "FACTORY_CENTRE_" << i << "=" << game->getFactories()->getCentre(i)->getTilesAsString() << std::endl;
    }
    for (int i = 0; i < game->getFactories()->getFactoriesNum(); i++)
    {
        saveToFile << "FACTORY_" << i << "=" << game->getFactories()->getFactory(i)->getLine()->getTilesAsString(false) << std::endl;
    }

    // Players Details
    for (int playerNum = 0; playerNum < game->getPlayers()->getPlayersNum(); playerNum++)
    {
        saveToFile << "PLAYER_" << playerNum << "_NAME=" << game->getPlayers()->getPlayer(playerNum)->getPlayerName() << std::endl;
        saveToFile << "PLAYER_" << playerNum << "_SCORE=" << game->getPlayers()->getPlayer(playerNum)->getPlayerScore() << std::endl;
        for (int i = 0; i < 5; i++)
        {
            saveToFile << "PLAYER_" << playerNum << "_PATTERN_LINE" << i << "=" << game->getPlayers()->getPlayer(playerNum)->getPlayerMosaic()->getPlayerPatternLines()->getLine(i)->getTilesAsString(true) << std::endl;
        }
        saveToFile << "PLAYER_" << playerNum << "_FLOOR_LINE=" << game->getPlayers()->getPlayer(playerNum)->getPlayerMosaic()->getPlayerBrokenTiles()->getLine()->getTilesAsString(true) << std::endl;
        for (int i = 0; i < 5; i++)
        {
            saveToFile << "PLAYER_" << playerNum << "_MOSAIC_" << i << "=" << game->getPlayers()->getPlayer(playerNum)->getPlayerMosaic()->getPlayerWall()->getLine(i)->getTilesAsString(true) << std::endl;
        }
    }

    // Current Player to make a move
    saveToFile << "CURRENT_PLAYER=" << currentPlayer % game->getPlayers()->getPlayersNum() << std::endl;
}

gamePtr LoadSave::loadFile(std::string loadFile, int &currentPlayer)
{
    Game *game = new Game();
    bool found = false;
    while (found == false)
    {
        std::ifstream checkFile(loadFile);
        // Check if file exists
        if (!checkFile && (found == false))
        {
            std::cout << "File was not found, please enter another file: " << std::endl;
            std::string filename;
            std::cin >> filename;

            loadFile = filename;
        }
        else
        {
            found = true;
        }
    }

    // Reading file in
    std::ifstream savedFile(loadFile);

    // while loop to read everything
    // bool playersAndFactoriesCreated = false;
    std::string line;
    int playersNum = 0;
    int centresNum = 0;
    bool advMode = false;
    bool greyMode = false;
    while (getline(savedFile, line))
    {
        std::string data;

        // Advanced Mode boolean
        if (line.find("ADV_MODE") != std::string::npos)
        {
            getData(line, data);

            // Splitting data into individual characters
            // dl = data.length();
            try
            {
                advMode = std::stoi(data);
            }
            catch (std::invalid_argument const &e)
            {
                std::cout << "Invalid adv mode boolean from save file." << std::endl;
            }
        }

        // Grey Mode boolean
        if (line.find("GREY_MODE") != std::string::npos)
        {
            getData(line, data);

            // Splitting data into individual characters
            // dl = data.length();
            try
            {
                greyMode = std::stoi(data);
            }
            catch (std::invalid_argument const &e)
            {
                std::cout << "Invalid grey mode boolean from save file." << std::endl;
            }
        }

        // number of players
        if (line.find("NUMBER_OF_PLAYERS") != std::string::npos)
        {
            getData(line, data);

            // Splitting data into individual characters
            // dl = data.length();
            try
            {
                playersNum = std::stoi(data);
                std::cout << "DEBUG: Number of players: " << playersNum << std::endl;
            }
            catch (std::invalid_argument const &e)
            {
                std::cout << "Invalid number of players from save file." << std::endl;
            }
        }

        // number of centres
        if (line.find("NUMBER_OF_CENTRES") != std::string::npos)
        {
            getData(line, data);

            // Splitting data into individual characters
            // dl = data.length();
            try
            {
                centresNum = std::stoi(data);
            }
            catch (std::invalid_argument const &e)
            {
                std::cout << "Invalid number of centres from save file." << std::endl;
            }
        }
    }
    std::cout << "DEBUG: createFactoriesAndPlayers(): " << playersNum << "," << centresNum << std::endl;
    game->createFactoriesAndPlayers(playersNum, centresNum, advMode, greyMode);

    // Reading file in
    std::ifstream savedFile2(loadFile);
    while (getline(savedFile2, line))
    {
        std::string data;
        int k, dl;

        /* FACTORIES */
        // Finding keyword line
        if (line.find("BAG") != std::string::npos)
        {
            getData(line, data);

            // Splitting data into individual characters
            dl = data.length();
            for (k = 0; k < dl; k++)
            {
                game->getBag()->addTileToBack(data[k]);
            }
        }

        if (line.find("LID") != std::string::npos)
        {
            getData(line, data);

            dl = data.length();
            for (k = 0; k < dl; k++)
            {
                game->getLid()->addTileToBack(data[k]);
            }
        }
        for (int i = 0; i < game->getFactories()->getCentresNum(); i++)
        {
            std::string factory = "FACTORY_CENTRE_";
            factory += std::to_string(i);
            if (line.find(factory) != std::string::npos)
            {
                getData(line, data);

                dl = data.length();
                for (k = 0; k < dl; k++)
                {
                    char tile = data[k];
                    if (tile != 'F')
                    {

                        game->getFactories()->getCentre(i)->addTile(tile);
                    }
                    else if (tile == 'F')
                    {
                        game->getFactories()->getCentre(i)->addTile(FIRSTPLAYER);
                    }
                }
            }
        }

        for (int i = 0; i < game->getFactories()->getFactoriesNum(); i++)
        {
            std::string factory = "FACTORY_";
            factory += std::to_string(i);
            if (line.find(factory) != std::string::npos)
            {
                getData(line, data);

                dl = data.length();
                for (k = 0; k < dl; k++)
                {
                    game->getFactories()->getFactory(i)->getLine()->addTileToBack(data[k]);
                }
            }
        }

        // PLAYERS
        for (int playerNum = 0; playerNum < playersNum; playerNum++)
        {
            std::string playerNumAsString = std::to_string(playerNum);
            if (line.find("PLAYER_" + playerNumAsString + "_NAME") != std::string::npos)
            {
                getData(line, data);
                game->getPlayers()->getPlayer(playerNum)->setPlayerName(data);
            }

            if (line.find("PLAYER_" + playerNumAsString + "_SCORE") != std::string::npos)
            {
                getData(line, data);
                game->getPlayers()->getPlayer(playerNum)->setPlayerScore(stoi(data));
            }

            for (int i = 0; i < 5; i++)
            {
                std::string playerPattern = "PLAYER_" + playerNumAsString + "_PATTERN_LINE";
                playerPattern += std::to_string(i);
                if (line.find(playerPattern) != std::string::npos)
                {
                    getData(line, data);

                    dl = data.length();
                    for (k = 0; k < dl; k++)
                    {
                        if (data[k] == NOTILE)
                        {
                            game->getPlayers()->getPlayer(playerNum)->getPlayerMosaic()->getPlayerPatternLines()->getLine(i)->removeTile(i);
                        }
                        else
                        {
                            game->getPlayers()->getPlayer(playerNum)->getPlayerMosaic()->getPlayerPatternLines()->getLine(i)->addTileToBack(data[k]);
                        }
                    }
                }
            }

            if (line.find("PLAYER_" + playerNumAsString + "_FLOOR_LINE") != std::string::npos)
            {
                getData(line, data);

                dl = data.length();
                for (k = 0; k < dl; k++)
                {
                    if (data[k] != NOTILE)
                    {
                        game->getPlayers()->getPlayer(playerNum)->getPlayerMosaic()->getPlayerBrokenTiles()->getLine()->addTileToBack(data[k]);
                    }
                    if (data[k] == FIRSTPLAYER) {
                        std::cout << "game->setFirstPlayerTokenTaken(true);" << std::endl;
                        game->setFirstPlayerTokenTaken(true);
                    }
                }
            }

            for (int i = 0; i < 5; i++)
            {
                std::string playerMosaic = "PLAYER_" + playerNumAsString + "_MOSAIC_";
                playerMosaic += std::to_string(i);
                if (line.find(playerMosaic) != std::string::npos)
                {
                    getData(line, data);

                    dl = data.length();
                    for (k = 0; k < dl; k++)
                    {
                        game->getPlayers()->getPlayer(playerNum)->getPlayerMosaic()->getPlayerWall()->getLine(i)->addTileToIndex(data[k], k);
                        if (data[k] == NOTILE || data[k] == '.')
                        {
                            game->getPlayers()->getPlayer(playerNum)->getPlayerMosaic()->getPlayerWall()->getLine(i)->removeTile(k);
                        }
                    }
                }
            }
        }

        /* CURRENT PLAYER */
        if (line.find("CURRENT_PLAYER") != std::string::npos)
        {
            getData(line, data);

            dl = data.length();
            for (k = 0; k < dl; k++)
            {
                std::string s = "";
                s.push_back(data[k]);
                currentPlayer = std::stoi(s);
            }
        }
    }
    return game;
}

// Getting the data after the '='
void LoadSave::getData(std::string line, std::string &data)
{
    int ll;
    char e = '=';
    size_t found = line.find(e);
    int el = 0;
    if (found != std::string::npos)
    {
        el = found + 1;
    }
    // Getting the line length
    ll = line.length();

    data = line.substr(el, ll - el);
}
