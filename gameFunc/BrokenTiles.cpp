#include "BrokenTiles.h"


BrokenTiles::BrokenTiles(bool sixTileMode) {
    if (sixTileMode) {
        brokenTilesNum = ADV_MAX_BROKEN_TILES;
    }
    else {
        brokenTilesNum = NORMAL_MAX_BROKEN_TILES;
    }
    brokenTiles = new Line(brokenTilesNum);
}

BrokenTiles::~BrokenTiles() {
    delete brokenTiles;
}

linePtr BrokenTiles::getLine() {
    return brokenTiles;
}

int BrokenTiles::getPenaltyPoints() {
    if (brokenTiles->getTilesNumber() == 0) {
        return NO_PENALTY;
    }
    else if (brokenTiles->getTilesNumber() == 1) {
        return ONE_TILE_PENALTY;
    }
    else if (brokenTiles->getTilesNumber() == 2) {
        return TWO_TILE_PENALTY;
    }
    else if (brokenTiles->getTilesNumber() == 3) {
        return THREE_TILE_PENALTY;
    }
    else if (brokenTiles->getTilesNumber() == 4) {
        return FOUR_TILE_PENALTY;
    }
    else if (brokenTiles->getTilesNumber() == 5) {
        return FIVE_TILE_PENALTY;
    }
    else if (brokenTiles->getTilesNumber() == 6) {
        return SIX_TILE_PENALTY;
    }
    else if (brokenTiles->getTilesNumber() == 7) {
        return SEVEN_TILE_PENALTY;
    }
    else {
        return EIGHT_TILE_PENALTY;
    }
}

void BrokenTiles::moveAllTilesToLid(Lid *lid) {
    for (int i = 0; i < brokenTiles->size(); i++) {
        if (brokenTiles->hasTile(i)) {
            // do not add the tile to lid if it is the Firstplayer token
            if (brokenTiles->getTileColour(i) == FIRSTPLAYER) {
                brokenTiles->removeTile(i);
            }
            else {
                lid->addTileToBack(brokenTiles->removeTile(i));
            }
        }
    }
}