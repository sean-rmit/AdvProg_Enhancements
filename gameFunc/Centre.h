#ifndef FactoryCentre
#define FactoryCentre

#include <vector>
#include <string>

#include "Tiles.h"
#include "painter.h"

class Centre {
public:

    // Constructor
    Centre();
    //Deconstructors
    ~Centre();

    // Copy constructor
    Centre(Centre& other);

    // Returns current size of factory
    int size();

    // Adds tiles to factory
    void addTile(char tileP);

    char getTileColour(int index);

    // Removes tiles from a factory
    char removeTile(int index);

    // Removes all tiles from factories
    void clear();

    std::string getTilesAsString(bool painted);

private:

    std::vector<char> centreTiles;
    Painter *painter;
};

typedef Centre* centrePtr;

#endif // Factory Centre