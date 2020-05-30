void newGamePage(int playersNum, int centresNum, int seed)
{
    //line 1
    printString("=", PAGEWIDTH);
    std::cout << std::endl;

    //line 2
    printString(" ", PAGEWIDTH / 2 - 4); //4 = half of letters in NEW GAME
    std::cout << "NEW GAME";
    std::cout << std::endl;

    //line 3
    printString("=", PAGEWIDTH);
    std::cout << std::endl;
    std::cout << std::endl;

    // game initialised
    Game *game = new Game(playersNum, centresNum, seed);

    // take in player names
    for (int i = 0; i < playersNum; i++)
    {
        std::cout << "Enter a name for player :" << i + 1 << std::endl;
        std::cout << "> ";
        std::string playerName;
        std::cin >> playerName;
        game->getPlayer(i)->setPlayerName(playerName);
    }

    game->getBag()->fillBagWithTiles(seed);
    if (centresNum == 1) {
        game->getFactories()->getCentre(0)->addTile(FIRSTPLAYER);
    }
    
    bool gameOngoing = true;
    std::cout << "Let’s Play!\n"
              << std::endl;
    std::cout << "== INSTRUCTIONS ==" << std::endl;
    std::cout << "Make a move: turn <factory index> <tile colour> <patternline index>" << std::endl;
    std::cout << "Save the game: save" << std::endl;
    std::cout << "Quit the game: quit" << std::endl;
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
            std::cout << game->getPlayer(playerNum)->getPlayerName() << std::endl;

            printFactories(game->getFactories());
            std::cout << std::endl;
            printPlayerMosaic(game->getPlayer(playerNum));
            bool validMove = false;
            // loop until valid move is made
            while (!validMove)
            {
                std::cout << game->getPlayer(playerNum)->getPlayerName() << "'s turn to make a move:" << std::endl;
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
                    save->saveFile(filename, game->getPlayers(), game->getFactories(), game->getBag(), game->getLid(), turnCounter);
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
                if (!validMove)
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
                game->finaliseGame();
                roundOngoing = false;
                gameOngoing = false;
            }
        }
    }
    std::cout << "=== GAME OVER ===" << std::endl;
    delete game;
}