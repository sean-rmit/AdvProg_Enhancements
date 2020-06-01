#include "Mosaic.h"

Mosaic::Mosaic(bool advMode, bool greyMode) {
    playerWall = new Wall(advMode, greyMode);
    playerPatternLines = new PatternLines(advMode);
    playerBrokenTiles = new BrokenTiles(advMode);
}

Mosaic::~Mosaic() {
    delete playerWall;
    delete playerPatternLines;
}

wallPtr Mosaic::getPlayerWall() {
    return playerWall;
}

patternLinesPtr Mosaic::getPlayerPatternLines() {
    return playerPatternLines;
}

brokenTilesPtr Mosaic::getPlayerBrokenTiles() {
    return playerBrokenTiles;
}

void Mosaic::putTileToPatternLine(char tile, int patternLineIndex) {
    playerPatternLines->getLine(patternLineIndex)->addTileToBack(tile);
}

void Mosaic::putTileToBrokenTiles(char tile) {
    playerBrokenTiles->getLine()->addTileToBack(tile);
}