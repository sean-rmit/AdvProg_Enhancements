#ifndef UTILS_H
#define UTILS_H

#include <ostream>

#include "game.h"

#define PLAYER_MOSAIC_CONSTRAINT_ON_CONSOLE 21
#define GAP_SIZE                            4
#define BROKENLINE_GAP_SIZE                 7

void printString(std::string s, int num);
void printInstructions(int numCentres);
void printFactories(Factories *factories);
void printPlayerMosaics(Players *players, bool sixTileMode);
void printPlayerPoints(Players *players);
void printGreyModeTiltingUI(Player *player, int patternLineIndex, bool instructions);
void printSixTileModePrompt();
void printGreyModePrompt();
void printEndGameMessage(Players *players, bool sixTileMode);

#endif // UTILS_H