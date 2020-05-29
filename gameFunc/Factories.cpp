#include "Factories.h"
#include <iostream>
#include <string>
#include <exception>

Factories::Factories(int numPlayers) {
    if (numPlayers == 2) {
        factoriesNum == FACTORIES_NUM_TWO_PLAYERS;
    }
    else if (numPlayers == 3) {
        factoriesNum == FACTORIES_NUM_THREE_PLAYERS;
    }
    else if (numPlayers == 4) {
        factoriesNum == FACTORIES_NUM_FOUR_PLAYERS;
    }
    else {
        std::cout << "Invalid number of players" << std::endl;
    }

    factories = new factoryPtr[factoriesNum];
    for (int i = 0; i < factoriesNum; i++)
    {
        Factory *factory = new Factory();
        factories[i] = factory;
    }
}
Factories::~Factories() {
    for (int i = 0; i < factoriesNum; i++)
    {
        delete factories[i];
    }
    delete factories;
}

Factories::Factories(Factories& other) {

}

int Factories::getFactoriesNum() {
    return factoriesNum;
}

factoryPtr Factories::getFactory(int index) {
    try
    {
        if (index < 0 || index > factoriesNum-1)
        {
            throw "Out of Bounds Exception!";
        }
    }
    catch (char const *e)
    {
        std::cout << "Error! Factory has exceeded 4 factories! ";
        std::cout << e << std::endl;
    }
    return factories[index];
}