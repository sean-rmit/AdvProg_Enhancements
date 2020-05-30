#ifndef UTILS_H
#define UTILS_H

#include <ostream>

#include "game.h"

#define PLAYER_MOSAIC_CONSTRAINT_ON_CONSOLE 21
#define GAP_SIZE                            4

void printString(std::string s, int num);
void printFactories(Factories *factories);
void printPlayerMosaic(Player *player);
void printPlayerMosaics(Players *players);
void printPlayerPoints(Players *players);



#endif // UTILS_H