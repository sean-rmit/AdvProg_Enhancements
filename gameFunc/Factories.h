#ifndef GameFactories
#define GameFactories

#include "Factory.h"
#include "Centre.h"

#define FACTORIES_NUM_TWO_PLAYERS 5
#define FACTORIES_NUM_THREE_PLAYERS 7
#define FACTORIES_NUM_FOUR_PLAYERS 9

class Factories {
public:

    // Constructor
    Factories(int numPlayers, int numCentres);
    // Deconstructor
    ~Factories();

    // copy constructor
    Factories(Factories& other);
    // get factory object at given index
    factoryPtr getFactory(int index);
    centrePtr getCentre(int index);

    int getFactoriesNum();
    int getCentresNum();

private:
    factoryPtr *factories;
    centrePtr *centres;
    int factoriesNum;
    int centresNum;
};

typedef Factories* factoriesPtr;

#endif // Game Factories