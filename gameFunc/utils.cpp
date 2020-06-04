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

void printMainMenuTemplate()
{
    //line 1
    printString("=", PAGEWIDTH);
    std::cout << std::endl;

    //line 2
    printString(" ", PAGEWIDTH / 2 - 2); //3 = half of letters in AZUL
    printf(BOLD_TEXT);
    printf(RED_TEXT);
    std::cout << "A";
    printf(YELLOW_TEXT);
    std::cout << "Z";
    printf(GREEN_TEXT);
    std::cout << "U";
    printf(DARKBLUE_TEXT);
    std::cout << "L";
    std::cout << std::endl;
    printf(RESET);

    //line 3
    printString("=", PAGEWIDTH);
    std::cout << std::endl;
    std::cout << std::endl;

    //line 4
    printString(" ", PAGEWIDTH / 2 - 10);
    std::cout << "New Game < enter 'N'";
    std::cout << std::endl;
    std::cout << std::endl;

    //line 5
    printString(" ", PAGEWIDTH / 2 - 10);
    std::cout << "Load Game < enter 'L'";
    std::cout << std::endl;
    std::cout << std::endl;

    //line 5
    printString(" ", PAGEWIDTH / 2 - 10);
    std::cout << "Credits < enter 'C'";
    std::cout << std::endl;
    std::cout << std::endl;

    //line 6
    printString(" ", PAGEWIDTH / 2 - 10);
    std::cout << "Quit Game < enter 'Q'";
    std::cout << std::endl;
    std::cout << std::endl;
}

void printInstructions(int numCentres)
{
    std::cout << "== INSTRUCTIONS ==" << std::endl;
    // if (numCentres == 1) {

    // }
    // else if (numCentres == 2) {
    //     std::cout << "Make a move: turn <Factory Tndex> <Tile Colour> <PatternLine Index> <Target Centre>" << std::endl;
    // }
    std::cout << "Make a move: type 'turn <Factory Tndex> <Tile Colour> <Patternline Index>'" << std::endl;
    std::cout << "Further assistance: type 'help'" << std::endl;
    std::cout << "Save the game: type 'save'" << std::endl;
    std::cout << "Quit the game: type 'quit'" << std::endl;
}

void printFactories(Factories *factories)
{
    std::cout << "Factories:" << std::endl;
    printString("=", 20);
    std::cout << std::endl;
    for (int i = 0; i < factories->getCentresNum(); i++)
    {
        std::cout << i << " - Centre : " << factories->getCentre(i)->getTilesAsString(true) << std::endl;
    }
    for (int i = 0; i < factories->getFactoriesNum(); i++)
    {
        std::cout << i + factories->getCentresNum();
        if (i + factories->getCentresNum() < 10)
        {
            std::cout << " ";
        }
        std::cout << "- Factory: ";
        std::cout << factories->getFactory(i)->getLine()->getTilesAsString(false, true) << std::endl;
    }
    printString("=", 20);
}

void printMosaic(Mosaic *mosaic, bool sixTileMode, bool greyMode)
{
    int mosaicIndexUI = 1;
    for (int i = 0; i < mosaic->getPlayerPatternLines()->getPatternLinesNum(); i++)
    {
        std::cout << mosaicIndexUI << ": ";
        mosaicIndexUI++;
        for (int j = 0; j < mosaic->getPlayerPatternLines()->getPatternLinesNum() - i; j++)
        {
            std::cout << " ";
        }
        std::cout << mosaic->getPlayerPatternLines()->getLine(i)->getTilesAsString(true, true);
        std::cout << " || ";
        if (greyMode)
        {
            std::cout << mosaic->getPlayerWall()->getLine(i)->getTilesAsString(true, true) << std::endl;
        }
        else
        {
            std::cout << mosaic->getPlayerWall()->getTilesAsStringFixedWallMode(i) << std::endl;
        }
    }
    std::cout << mosaicIndexUI << ": broken: " << mosaic->getPlayerBrokenTiles()->getLine()->getTilesAsString(true, true) << std::endl;
}

void printPlayerMosaics(Players *players, bool sixTileMode, bool greyMode)
{
    std::cout << "Mosaics of Players:" << std::endl;
    // print player names
    int spacesNeeded = PLAYER_MOSAIC_CONSTRAINT_ON_CONSOLE;
    if (sixTileMode)
    {
        // one extra slot of tile in pattern line and one in wall mosaic during 6-tile mode
        spacesNeeded += 2;
    }
    for (int playerNum = 0; playerNum < players->getPlayersNum(); playerNum++)
    {
        std::string playerName = players->getPlayer(playerNum)->getPlayerName();
        std::cout << playerName << ":";
        printString(" ", spacesNeeded - playerName.size());
    }
    std::cout << std::endl;

    int mosaicIndexUI = 1;
    // print players mosaic lines
    int patternLinesNum = players->getPlayer(0)->getPlayerMosaic()->getPlayerPatternLines()->getPatternLinesNum();
    for (int i = 0; i < patternLinesNum; i++)
    {
        for (int playerNum = 0; playerNum < players->getPlayersNum(); playerNum++)
        {
            std::cout << mosaicIndexUI << ": ";
            for (int j = 0; j < patternLinesNum - i; j++)
            {
                std::cout << " ";
            }
            // pattern line
            std::cout << players->getPlayer(playerNum)->getPlayerMosaic()->getPlayerPatternLines()->getLine(i)->getTilesAsString(true, true);
            std::cout << " || ";
            // wall
            if (greyMode)
            {
                std::cout << players->getPlayer(playerNum)->getPlayerMosaic()->getPlayerWall()->getLine(i)->getTilesAsString(true, true);
            }
            else
            {
                std::cout << players->getPlayer(playerNum)->getPlayerMosaic()->getPlayerWall()->getTilesAsStringFixedWallMode(i);
            }
            printString(" ", GAP_SIZE);
        }
        mosaicIndexUI++;
        std::cout << std::endl;
    }
    spacesNeeded = BROKENLINE_GAP_SIZE;
    if (sixTileMode)
    {
        // one extra slot of tile in broken line during 6-tile mode
        spacesNeeded += 1;
    }
    for (int playerNum = 0; playerNum < players->getPlayersNum(); playerNum++)
    {
        std::cout << mosaicIndexUI << ":broken: " << players->getPlayer(playerNum)->getPlayerMosaic()->getPlayerBrokenTiles()->getLine()->getTilesAsString(true, true);
        printString(" ", spacesNeeded);
    }
    std::cout << std::endl;
}

void printPlayerPoints(Players *players)
{
    std::cout << std::endl;
    for (int i = 0; i < players->getPlayersNum(); i++)
    {
        std::cout << players->getPlayer(i)->getPlayerName() << "'s score: " << players->getPlayer(i)->getPlayerScore() << std::endl;
    }
    std::cout << std::endl;
}

void printGreyModeTiltingUI(Player *player, int patternLineIndex, bool instructions)
{
    if (instructions)
    {
        std::cout << "Wall Tilting Phase - Player: " << player->getPlayerName() << std::endl;
        std::cout << "Choose the column index of your wall you would like to place your tile" << std::endl;
        std::cout << "for the targeted line index with symbol '>>'" << std::endl;
    }

    printString(" ", player->getPlayerMosaic()->getPlayerPatternLines()->getPatternLinesNum() + 10);
    for (int i = 0; i < player->getPlayerMosaic()->getPlayerWall()->getWallLinesNum(); i++)
    {
        std::cout << i << " " << std::endl;
    }

    for (int i = 0; i < player->getPlayerMosaic()->getPlayerPatternLines()->getPatternLinesNum(); i++)
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
        for (int j = 0; j < player->getPlayerMosaic()->getPlayerPatternLines()->getPatternLinesNum() - i; j++)
        {
            std::cout << " ";
        }
        std::cout << player->getPlayerMosaic()->getPlayerPatternLines()->getLine(i)->getTilesAsString(true, true);
        std::cout << " || ";
        std::cout << player->getPlayerMosaic()->getPlayerWall()->getLine(i)->getTilesAsString(true, true) << std::endl;
    }
}

void printSixTileModePrompt()
{
    printString("=", 30);
    std::cout << std::endl;
    std::cout << "Option A: Classic Mode" << std::endl;
    printString("=", 30);
    std::cout << std::endl;
    std::cout << "Play azul with the classic 5x5 mosaic wall." << std::endl;
    std::cout << std::endl;
    printSampleMosaicTemplate(false, false);
    std::cout << std::endl;
    printString("=", 30);
    std::cout << std::endl;
    std::cout << "Option B: Six Tile Mode" << std::endl;
    printString("=", 30);
    std::cout << std::endl;
    std::cout << "Play azul with a 6x6 mosaic wall, which includes the additional tile colour ";
    printf(ORANGE_TEXT);
    std::cout << "Orange" << std::endl;
    printf(RESET);
    std::cout << std::endl;
    printSampleMosaicTemplate(true, false);
    std::cout << std::endl;
    std::cout << "Enter A(Classic Mode) or B(Six Tile Mode):" << std::endl;
}

void printSampleMosaicTemplate(bool sixTileMode, bool greyMode)
{
    Mosaic *mosaic = new Mosaic(sixTileMode, greyMode);
    Lid *lid = new Lid();
    // classic mode sample
    if (!sixTileMode && !greyMode)
    {
        mosaic->getPlayerPatternLines()->getLine(0)->addTileToBack(YELLOW);
        mosaic->getPlayerPatternLines()->getLine(1)->addTileToBack(RED);
        mosaic->getPlayerPatternLines()->getLine(3)->addTileToBack(LIGHTBLUE);
        mosaic->getPlayerPatternLines()->getLine(3)->addTileToBack(LIGHTBLUE);
        mosaic->getPlayerPatternLines()->getLine(3)->addTileToBack(LIGHTBLUE);
        mosaic->getPlayerWall()->addTile(RED, 0, lid);
        mosaic->getPlayerWall()->addTile(YELLOW, 1, lid);
        mosaic->getPlayerWall()->addTile(DARKBLUE, 2, lid);
        mosaic->getPlayerWall()->addTile(DARKBLUE, 3, lid);
        mosaic->getPlayerWall()->addTile(RED, 3, lid);
        mosaic->getPlayerWall()->addTile(BLACK, 4, lid);
    }
    // six tile mode sample
    else if (sixTileMode && !greyMode) {
        mosaic->getPlayerPatternLines()->getLine(0)->addTileToBack(DARKBLUE);
        mosaic->getPlayerPatternLines()->getLine(2)->addTileToBack(ORANGE);
        mosaic->getPlayerPatternLines()->getLine(2)->addTileToBack(ORANGE);
        mosaic->getPlayerPatternLines()->getLine(2)->addTileToBack(ORANGE);
        mosaic->getPlayerPatternLines()->getLine(3)->addTileToBack(RED);
        mosaic->getPlayerPatternLines()->getLine(5)->addTileToBack(YELLOW);
        mosaic->getPlayerPatternLines()->getLine(5)->addTileToBack(YELLOW);
        mosaic->getPlayerPatternLines()->getLine(5)->addTileToBack(YELLOW);
        mosaic->getPlayerWall()->addTile(LIGHTBLUE, 0, lid);
        mosaic->getPlayerWall()->addTile(YELLOW, 1, lid);
        mosaic->getPlayerWall()->addTile(ORANGE, 3, lid);
        mosaic->getPlayerWall()->addTile(DARKBLUE, 3, lid);
        mosaic->getPlayerWall()->addTile(BLACK, 4, lid);
        mosaic->getPlayerWall()->addTile(LIGHTBLUE, 5, lid);
    }
    // grey mode sample
    else if (greyMode) {
        mosaic->getPlayerPatternLines()->getLine(0)->addTileToBack(LIGHTBLUE);
        mosaic->getPlayerPatternLines()->getLine(1)->addTileToBack(YELLOW);
        mosaic->getPlayerPatternLines()->getLine(1)->addTileToBack(YELLOW);
        mosaic->getPlayerPatternLines()->getLine(3)->addTileToBack(RED);
        mosaic->getPlayerWall()->getLine(0)->addTileToIndex(BLACK, 2);
        mosaic->getPlayerWall()->getLine(0)->addTileToIndex(YELLOW, 3);
        mosaic->getPlayerWall()->getLine(1)->addTileToIndex(RED, 3);
        mosaic->getPlayerWall()->getLine(4)->addTileToIndex(DARKBLUE, 0);
        if (sixTileMode) {
            mosaic->getPlayerPatternLines()->getLine(2)->addTileToBack(ORANGE);
            mosaic->getPlayerPatternLines()->getLine(2)->addTileToBack(ORANGE);
            mosaic->getPlayerPatternLines()->getLine(5)->addTileToBack(YELLOW);
            mosaic->getPlayerPatternLines()->getLine(5)->addTileToBack(YELLOW);
            mosaic->getPlayerPatternLines()->getLine(5)->addTileToBack(YELLOW);
            mosaic->getPlayerWall()->getLine(2)->addTileToIndex(ORANGE, 2);
            mosaic->getPlayerWall()->getLine(5)->addTileToIndex(RED, 0);
            mosaic->getPlayerWall()->getLine(5)->addTileToIndex(ORANGE, 1);
        }
        
    }

    printMosaic(mosaic, sixTileMode, greyMode);
    delete mosaic;
    delete lid;
}

void printGreyModePrompt(bool sixTileMode)
{
    printString("=", 30);
    std::cout << std::endl;
    std::cout << "Option A: Fixed Wall Mode" << std::endl;
    printString("=", 30);
    std::cout << std::endl;
    std::cout << "Play azul with a mosaic wall with fixed colour positions" << std::endl;
    std::cout << std::endl;
    printSampleMosaicTemplate(sixTileMode, false);
    std::cout << std::endl;
    printString("=", 30);
    std::cout << std::endl;
    std::cout << "Option B: Grey Mode" << std::endl;
    printString("=", 30);
    std::cout << std::endl;
    std::cout << "Play azul with an unfixed grey mosaic wall. Wall colour restrictions still apply. Design your own mosaic wall!" << std::endl;
    std::cout << std::endl;
    printSampleMosaicTemplate(sixTileMode, true);
    std::cout << std::endl;
    std::cout << "Enter A(Fixed Wall Mode) or B(Grey Mode):" << std::endl;
}

void printEndGameMessage(Players *players, bool sixTileMode, bool greyMode)
{
    std::cout << "A player has completed a horizontal line on their wall, the game ends!" << std::endl;
    std::cout << std::endl;
    printPlayerMosaics(players, sixTileMode, greyMode);
    std::cout << std::endl;
}

void printLoadGameTitle() {
    //line 1
    printString("=", PAGEWIDTH);
    std::cout << std::endl;

    //line 2
    printString(" ", PAGEWIDTH / 2 - 4);
    std::cout << "LOAD GAME";
    std::cout << std::endl;

    //line 3
    printString("=", PAGEWIDTH);
    std::cout << std::endl;
    std::cout << std::endl;
}

void printNewGameTitle() {
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
}

void printHelpGuideMosaic() {
    Line *line = new Line(4);
    Line *line1 = new Line (4);
    Line *line2 = new Line (2);
    PatternLines *patternlines = new PatternLines(false);
    line->addTileToBack(YELLOW);
    line->addTileToBack(YELLOW);
    line->addTileToBack(RED);
    line->addTileToBack(DARKBLUE);
    line1->addTileToBack(BLACK);
    line1->addTileToBack(LIGHTBLUE);
    line1->addTileToBack(BLACK);
    line1->addTileToBack(YELLOW);
    line2->addTileToBack(RED);
    line2->addTileToBack(DARKBLUE);
    patternlines->getLine(0)->addTileToBack(RED);
    for (int i = 0; i < 3; i++) {
        patternlines->getLine(3)->addTileToBack(LIGHTBLUE);
        patternlines->getLine(4)->addTileToBack(BLACK);
    }
    
    std::cout << "|BEFORE|";
    printString(" ", 42);
    std::cout << "|AFTER|" << std::endl;
    std::cout << "Factories:";
    printString(" ", 40);
    std::cout << "Factories:" << std::endl;
    printString("=", 20);
    printString(" ", 30);
    printString("=", 20);
    std::cout << std::endl;
    std::cout << "0 - Centre:";
    printString(" ", 39);
    std::cout << "0 - Centre:" << line2->getTilesAsString(false, true);
    std::cout << " << Excess tiles from factory gets placed into centre" << std::endl;
    std::cout << "1 - Factory:" << line->getTilesAsString(true, true);
    for (int i = 0; i < line->size(); i++) {
        line->removeTile(i);
    }
    std::cout << " << Factory chosen";
    printString(" ", 16);
    std::cout << "1 - Factory:" << line->getTilesAsString(true, true);
    std::cout << " << All tiles removed from selected factory" << std::endl;
    std::cout << "2 - Factory:" << line1->getTilesAsString(true, true);
    printString(" ", 34);
    std::cout << "2 - Factory:" << line1->getTilesAsString(true, true) << std::endl;
    printString("=", 20);
    printString(" ", 30);
    printString("=", 20);
    std::cout << std::endl;
    std::cout << "Your pattern line:";
    printString(" ", 32);
    std::cout << "Your pattern line:" << std::endl;
    for (int i = 0; i < patternlines->getPatternLinesNum(); i++) {
        std::cout << i + 1 << ":";
        printString(" ", 5 - i);
        std::cout << patternlines->getLine(i)->getTilesAsString(true, true);
        if (i + 1 == 3) {
            std::cout << " << Pattern line chosen";
            printString(" ", 19);
            patternlines->getLine(i)->addTileToBack(YELLOW);
            patternlines->getLine(i)->addTileToBack(YELLOW);
        }
        else {
            printString(" ", 42);
        }
        std::cout << i + 1 << ":";
        printString(" ", 5 - i);
        std::cout << patternlines->getLine(i)->getTilesAsString(true, true);
        if (i + 1 == 3) {
            std::cout << " << 2 Y tiles from factory is moved here";
        }
        std::cout << std::endl;
    }
    delete line;
    delete line1;
    delete line2;
    delete patternlines;
}

void printHelpGuide() {
    printString("=", PAGEWIDTH);
    std::cout << std::endl;
    std::cout << "Guide:" << std::endl;
    std::cout << "1. Choose a factory you would like to pick your tiles from." << std::endl;
    std::cout << "2. Decide on the tile colour you would like to select from the factory chosen." << std::endl;
    std::cout << "3. Choose a pattern line on your board to put your selected tiles in." << std::endl;
    std::cout << "4. Type 'turn <factory index> <tile colour> <pattern line index>'" << std::endl;
    std::cout << std::endl;
    std::cout << "Sample move: 'turn 1 Y 3'" << std::endl;
    std::cout << "Details:" << std::endl;
    std::cout << "Factory index chosen: 1" << std::endl;
    std::cout << "Tile Colour chosen: Y" << std::endl;
    std::cout << "Pattern line index chosen: 3" << std::endl;
    std::cout << std::endl;
    printHelpGuideMosaic();
    std::cout << std::endl;
    std::cout << "Enter any value to continue the game:" << std::endl;
    std::cout << ">";;
    std::string input;
    std::cin >> input;
}