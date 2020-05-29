#ifndef GameFactories
#define GameFactories

#include "Factory.h"

#define FACTORIES_NUM_TWO_PLAYERS 5
#define FACTORIES_NUM_THREE_PLAYERS 7
#define FACTORIES_NUM_FOUR_PLAYERS 9

class Factories {
public:

    // Constructor
    Factories(int numPlayers);
    // Deconstructor
    ~Factories();

    // copy constructor
    Factories(Factories& other);
    // get factory object at given index
    factoryPtr getFactory(int index);

    int getFactoriesNum();

private:
    factoryPtr *factories;
    int factoriesNum;
};

typedef Factories* factoriesPtr;

#endif // Game Factories