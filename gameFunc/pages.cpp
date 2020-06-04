#include <iostream>
#include <fstream>
#include <cstdio>
#include "pages.h"

void mainMenuPage(int seed)
{
    printMainMenuTemplate();

    bool mainMenuRunning = true;
    while (mainMenuRunning)
    {
        std::cout << "> ";
        char input = ' ';
        std::cin >> input;
        if (input == 'C' || input == 'c')
        {
            creditsPage();
        }
        else if (std::cin.eof() || input == 'Q' || input == 'q')
        {
            mainMenuRunning = false;
        }
        else if (input == 'N' || input == 'n')
        {
            printNewGameTitle();
            bool modsChosen = false;

            while (!modsChosen)
            {
                bool sixTileMode = false;
                bool greyMode = false;
                printSixTileModePrompt();
                std::cout << "> ";
                std::cin >> input;
                if (input == 'B' || input == 'b')
                {
                    std::cout << std::endl;
                    std::cout << "== Six Tile Mode chosen! ==" << std::endl;
                    std::cout << std::endl;
                    sixTileMode = true;
                }
                else if (input == 'A' || input == 'a')
                {
                    std::cout << std::endl;
                    std::cout << "== Classic Mode chosen! ==" << std::endl;
                    std::cout << std::endl;
                    sixTileMode = false;
                }
                else if (std::cin.eof())
                {
                    // if Ctrl+D is entered terminate the while loops
                    modsChosen = true;
                }
                else
                {
                    std::cout << std::endl;
                    std::cout << "WARNING: You have entered an invalid value. Classic Mode will be chosen." << std::endl;
                    std::cout << std::endl;
                }

                printGreyModePrompt(sixTileMode);
                std::cout << "> ";
                std::cin >> input;
                if (input == 'B' || input == 'b')
                {
                    std::cout << std::endl;
                    std::cout << "== Grey Mode chosen! ==" << std::endl;
                    std::cout << std::endl;
                    greyMode = true;
                }
                else if (input == 'A' || input == 'a')
                {
                    std::cout << std::endl;
                    std::cout << "== Fixed Wall Mode chosen! ==" << std::endl;
                    std::cout << std::endl;
                    greyMode = false;
                }
                else if (std::cin.eof())
                {
                    // if Ctrl+D is entered terminate the while loops
                    modsChosen = true;
                }
                else
                {
                    std::cout << std::endl;
                    std::cout << "WARNING: You have entered an invalid value. Fixed Wall Mode will be chosen." << std::endl;
                    std::cout << std::endl;
                }

                std::cout << "Number of players, min: 2  max: 4" << std::endl;
                std::cout << ">";
                int playersNum = 0;
                std::string playersNumAsString;
                std::cin >> playersNumAsString;
                int centresNum = 0;
                std::cout << "Number of centres, min: 1  max: 2 " << std::endl;
                std::cout << ">";
                std::string centresNumAsString;
                std::cin >> centresNumAsString;
                if (std::cin.eof())
                {
                    // if Ctrl+D is entered terminate the while loops
                    modsChosen = true;
                }
                try
                {
                    playersNum = std::stoi(playersNumAsString);
                    centresNum = std::stoi(centresNumAsString);
                }
                catch (std::invalid_argument const &e)
                {
                }
                if (playersNum >= 2 && playersNum <= 4 && centresNum >= 1 && centresNum <= 2)
                {
                    newGamePage(playersNum, centresNum, sixTileMode, greyMode, seed);
                    modsChosen = true;
                    mainMenuRunning = false;
                }
                else
                {
                    std::cout << "Invalid number of players or centres!" << std::endl;
                }
            }
        }
        else if (input == 'L' || input == 'l')
        {
            printLoadGameTitle();
            // User input for filename
            bool found = false;
            bool forcequit = false;
            bool back = false;
            std::string filename = "";
            while (!found)
            {
                std::cout << "Enter the filename you wish to load the game from, or type 'B' to go back to the main menu" << std::endl;
                std::cout << "> ";
                std::cin >> filename;
                std::ifstream checkFile(filename);
                // check for Ctrl+D
                if (std::cin.eof())
                {
                    found = true;
                    forcequit = true;
                }
                // check for B
                if (filename == "B" || filename == "b")
                {
                    found = true;
                    back = true;
                }
                // Check if file exists
                if (!checkFile && !found)
                {
                    std::cout << "File was not found. Please try again." << std::endl;
                }
                else
                {
                    found = true;
                }
            }
            if (!forcequit && !back)
            {
                loadGamePage(filename);
            }
            if (back)
            {
                printMainMenuTemplate();
            }
            else
            {
                mainMenuRunning = false;
            }
        }
        else
        {
            std::cout << "No such available input! Please try again." << std::endl;
        }
    }
}

void newGamePage(int playersNum, int centresNum, bool sixTileMode, bool greyMode, int seed)
{
    // game initialised
    Game *game = new Game(playersNum, centresNum, sixTileMode, greyMode, seed);

    // take in player names
    for (int i = 0; i < playersNum; i++)
    {
        std::cout << "Enter a name for player " << i + 1 << ":" << std::endl;
        std::cout << "> ";
        std::string input;
        std::cin >> input;
        // due to console constraint, name will be cut to max 14 letters
        std::string playerName = input.substr(0, 14);
        game->getPlayers()->getPlayer(i)->setPlayerName(playerName);
    }

    game->getBag()->fillBagWithTiles(seed, sixTileMode);
    if (centresNum == 1)
    {
        game->getFactories()->getCentre(0)->addTile(FIRSTPLAYER);
    }

    bool gameOngoing = true;
    std::cout << "Let’s Play!\n"
              << std::endl;
    printInstructions(centresNum);
    std::cout << std::endl;
    int turnCounter = 0;
    while (gameOngoing)
    {
        bool roundOngoing = true;
        // initialise the round (i.e. load factories with tiles)
        std::cout << "=== Start Round ===" << std::endl;
        printPlayerPoints(game->getPlayers());
        game->prepareNewRound();
        while (roundOngoing)
        {
            int playerNum = turnCounter % playersNum;
            std::cout << "TURN FOR PLAYER: ";
            std::cout << game->getPlayers()->getPlayer(playerNum)->getPlayerName() << std::endl;

            printFactories(game->getFactories());
            std::cout << std::endl;
            printPlayerMosaics(game->getPlayers(), sixTileMode, greyMode);
            bool validMove = false;
            // loop until valid move is made
            while (!validMove)
            {
                bool helpNeeded = false;
                std::cout << game->getPlayers()->getPlayer(playerNum)->getPlayerName() << "'s turn to make a move:" << std::endl;
                std::cout << "> ";
                std::string playerMove;
                std::cin >> playerMove;
                // if Ctrl+D is entered terminate the while loops
                if (std::cin.eof())
                {
                    validMove = true;
                    roundOngoing = false;
                    gameOngoing = false;
                    game->finaliseGame();
                }
                if (playerMove == "save")
                {
                    validMove = true;
                    roundOngoing = false;
                    gameOngoing = false;
                    std::cout << "Enter the filename (.txt) you wish to save to:" << std::endl;
                    std::cout << "> ";
                    std::string filename;
                    std::cin >> filename;
                    LoadSave *save = new LoadSave();
                    save->saveFile(filename, game, turnCounter);
                    delete save;
                }
                else if (playerMove == "quit")
                {
                    validMove = true;
                    roundOngoing = false;
                    gameOngoing = false;
                    game->finaliseGame();
                }
                else if (playerMove == "turn")
                {
                    validMove = game->playerMakesMove(playerNum);
                    if (validMove)
                    {
                        std::cout << "Turn Successful." << std::endl;
                    }
                }
                else if (playerMove == "help")
                {
                    helpNeeded = true;
                    printHelpGuide();
                    printFactories(game->getFactories());
                    std::cout << std::endl;
                    printPlayerMosaics(game->getPlayers(), sixTileMode, greyMode);
                }
                if (!validMove && !helpNeeded)
                {
                    std::cout << "Invalid Move. Please try again." << std::endl;
                    std::cout << "To make a move: turn <factory index> <tile colour> <patternline index>" << std::endl;
                    std::cout << "Further assistance: type 'help'" << std::endl;
                }
            }
            turnCounter++;
            // check if the round has ended (aka factories and centre are all empty)
            if (game->hasRoundEnded())
            {
                game->determineFirstPlayer(turnCounter);
                game->finaliseRound();
                roundOngoing = false;
            }
            if (game->hasGameEnded())
            {
                printEndGameMessage(game->getPlayers(), game->isSixTileMode(), game->isGreyMode());
                game->finaliseGame();
                roundOngoing = false;
                gameOngoing = false;
            }
        }
    }
    std::cout << "=== GAME OVER ===" << std::endl;
    delete game;
}

void loadGamePage(std::string filename)
{

    bool gameOngoing = true;
    int turnCounter = 0;
    int playersNum = 0;
    int centresNum = 0;
    LoadSave *load = new LoadSave();
    Game *game = load->loadFile(filename, turnCounter);
    playersNum = game->getPlayers()->getPlayersNum();
    centresNum = game->getFactories()->getCentresNum();
    std::cout << "=== Azul Game Successfully Loaded ===" << std::endl;
    std::cout << "Let’s Play!" << std::endl;
    printInstructions(centresNum);
    std::cout << std::endl;
    bool firstRoundSinceLoad = true;

    while (gameOngoing)
    {
        bool roundOngoing = true;
        // initialise the round (i.e. load factories with tiles)
        if (!firstRoundSinceLoad)
        {
            std::cout << "=== Start Round ===" << std::endl;
            printPlayerPoints(game->getPlayers());
            game->prepareNewRound();
        }
        else
        {
            // check if the round has ended (aka factories and centre are all empty)
            if (game->hasRoundEnded())
            {
                game->determineFirstPlayer(turnCounter);
                game->finaliseRound();
                roundOngoing = false;
            }
            if (game->hasGameEnded())
            {
                printEndGameMessage(game->getPlayers(), game->isSixTileMode(), game->isGreyMode());
                game->finaliseGame();
                roundOngoing = false;
                gameOngoing = false;
            }
            firstRoundSinceLoad = false;
        }

        while (roundOngoing)
        {
            int playerNum = turnCounter % playersNum;
            std::cout << "TURN FOR PLAYER: ";
            std::cout << game->getPlayers()->getPlayer(playerNum)->getPlayerName() << std::endl;

            printFactories(game->getFactories());
            std::cout << std::endl;
            printPlayerMosaics(game->getPlayers(), game->isSixTileMode(), game->isGreyMode());
            bool validMove = false;
            // loop until valid move is made
            while (!validMove)
            {
                bool helpNeeded = false;
                std::cout << game->getPlayers()->getPlayer(playerNum)->getPlayerName() << "'s turn to make a move:" << std::endl;
                std::cout << "> ";
                std::string playerMove;
                std::cin >> playerMove;

                // if Ctrl+D is entered terminate the while loops
                if (std::cin.eof())
                {
                    validMove = true;
                    roundOngoing = false;
                    gameOngoing = false;
                    game->finaliseGame();
                }

                if (playerMove == "save")
                {
                    validMove = true;
                    roundOngoing = false;
                    gameOngoing = false;
                    std::cout << "Enter the filename (.txt) you wish to save to:" << std::endl;
                    std::cout << "> ";
                    std::string filename;
                    std::cin >> filename;
                    LoadSave *save = new LoadSave();
                    save->saveFile(filename, game, turnCounter);
                    delete save;
                }
                else if (playerMove == "quit")
                {
                    validMove = true;
                    roundOngoing = false;
                    gameOngoing = false;
                    game->finaliseGame();
                }
                else if (playerMove == "turn")
                {
                    validMove = game->playerMakesMove(playerNum);
                    if (validMove)
                    {
                        std::cout << "Turn Successful." << std::endl;
                    }
                }
                else if (playerMove == "help")
                {
                    helpNeeded = true;
                    printHelpGuide();
                    printFactories(game->getFactories());
                    std::cout << std::endl;
                    printPlayerMosaics(game->getPlayers(), game->isSixTileMode(), game->isGreyMode());
                }
                if (!validMove && !helpNeeded)
                {
                    std::cout << "Invalid Move." << std::endl;
                    std::cout << "To make a move:" << std::endl;
                    std::cout << "turn <factory index> <tile colour> <patternline index>" << std::endl;
                }
            }
            turnCounter++;
            // check if the round has ended (aka factories and centre are all empty)
            if (game->hasRoundEnded())
            {
                game->determineFirstPlayer(turnCounter);
                game->finaliseRound();
                roundOngoing = false;
            }
            if (game->hasGameEnded())
            {
                printEndGameMessage(game->getPlayers(), game->isSixTileMode(), game->isGreyMode());
                game->finaliseGame();
                roundOngoing = false;
                gameOngoing = false;
            }
        }
    }

    std::cout << "=== GAME OVER ===" << std::endl;
    delete load;
    delete game;
}

void creditsPage()
{
    //line 1
    printString("=", PAGEWIDTH);
    std::cout << std::endl;

    //line 2
    printString(" ", PAGEWIDTH / 2 - 3); //3 = half of letters in CREDITS
    std::cout << "CREDITS";
    std::cout << std::endl;

    //line 3
    printString("=", PAGEWIDTH);
    std::cout << std::endl;
    std::cout << std::endl;

    //line 4
    printString(" ", PAGEWIDTH / 2 - 4);
    std::cout << "Design by";
    std::cout << std::endl;
    std::cout << std::endl;

    //line 5
    printString(" ", PAGEWIDTH / 2 - 8);
    std::cout << "Sean Tan < s3806690 >";
    std::cout << std::endl;

    //line 6
    printString(" ", PAGEWIDTH / 2 - 9);
    std::cout << "Aaron Soa < s3786067 >";
    std::cout << std::endl;

    //line 7
    printString(" ", PAGEWIDTH / 2 - 10);
    std::cout << "Amy Nguyen < s3783694 >";
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "New Game < enter 'N'" << std::endl;
    std::cout << "Load Game < enter 'L'" << std::endl;
    std::cout << "Quit Game < enter 'Q'" << std::endl;
}