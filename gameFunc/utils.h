#ifndef UTILS_H
#define UTILS_H

#include <ostream>

#include "game.h"

#define PLAYER_MOSAIC_CONSTRAINT_ON_CONSOLE 21
#define GAP_SIZE                            4

void printString(std::string s, int num);
void printInstructions(int numCentres);
void printFactories(Factories *factories);
void printPlayerMosaics(Players *players);
void printPlayerPoints(Players *players);
void printGreyModeTiltingUI(Player *player, int patternLineIndex, bool instructions);


#endif // UTILS_H