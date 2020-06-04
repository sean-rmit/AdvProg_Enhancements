#ifndef UTILS_H
#define UTILS_H

#include <ostream>

#include "game.h"

#define PAGEWIDTH       80
#define PLAYER_MOSAIC_CONSTRAINT_ON_CONSOLE 21
#define GAP_SIZE                            4
#define BROKENLINE_GAP_SIZE                 5

void printString(std::string s, int num);
void printMainMenuTemplate();
void printInstructions(int numCentres);
void printFactories(Factories *factories);
void printMosaic(Mosaic *mosaic, bool sixTileMode, bool greyMode);
void printPlayerMosaics(Players *players, bool sixTileMode, bool greyMode);
void printPlayerPoints(Players *players);
void printGreyModeTiltingUI(Player *player, int patternLineIndex, bool instructions);
void printSixTileModePrompt();
void printGreyModePrompt(bool sixTileMode);
void printEndGameMessage(Players *players, bool sixTileMode, bool greyMode);
void printSampleMosaicTemplate(bool sixTileMode, bool greyMode);
void printLoadGameTitle();
void printNewGameTitle();
void printHelpGuideMosaic();
void printHelpGuide();

#endif // UTILS_H