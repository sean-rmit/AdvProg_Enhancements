#ifndef TilesBag
#define TilesBag

#include "Tiles.h"
#include "Line.h"
#include "LinkedList.h"

#include <string>
#include <vector>
#include <random>

#define NORMAL_TILEBAG_SIZE 100
#define SIX_TILE_MODE_TILEBAG_SIZE    120

class Bag {
public:

    Bag();
    ~Bag();

    // copy constructor
    Bag(Bag& other);

    // return number of tiles in bag
    unsigned int size();

    // add tile to back of the linked list of bag
    void addTileToBack(char tile);

    // remove the tile at the front of the linked list of bag
    char removeTileFront();

    // removes all tiles from the linked list of bag
    void clearBag();

    // fill bag with tiles of random order, seed = 0 is assumed as no seed value given
    void fillBagWithTiles(int seed, bool sixTileMode);

    // print tiles contained in linked list of bag
    std::string getTilesAsString();

private:
    LinkedList* bag;
};

typedef Bag* bagPtr;

#endif // TilesBag