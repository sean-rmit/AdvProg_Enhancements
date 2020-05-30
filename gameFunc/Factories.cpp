#include "Factories.h"
#include <iostream>
#include <string>
#include <exception>

Factories::Factories(int numPlayers, int numCentres) {
    if (numPlayers == 2) {
        factoriesNum = FACTORIES_NUM_TWO_PLAYERS;
    }
    else if (numPlayers == 3) {
        factoriesNum = FACTORIES_NUM_THREE_PLAYERS;
    }
    else if (numPlayers == 4) {
        factoriesNum = FACTORIES_NUM_FOUR_PLAYERS;
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

    centresNum = numCentres;
    centres = new centrePtr[centresNum];
    for (int i = 0; i < centresNum; i++)
    {
        Centre *centre = new Centre();
        centres[i] = centre;
    }
}
Factories::~Factories() {
    for (int i = 0; i < factoriesNum; i++)
    {
        delete factories[i];
    }
    for (int i = 0; i < centresNum; i++)
    {
        delete centres[i];
    }
    delete factories;
    delete centres;
}

Factories::Factories(Factories& other) {

}

int Factories::getFactoriesNum() {
    return factoriesNum;
}

int Factories::getCentresNum() {
    return centresNum;
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
        std::cout << "Error! Factory index has exceeded total number of factories! ";
        std::cout << e << std::endl;
    }
    return factories[index];
}

centrePtr Factories::getCentre(int index) {
    try
    {
        if (index < 0 || index > centresNum-1)
        {
            throw "Out of Bounds Exception!";
        }
    }
    catch (char const *e)
    {
        std::cout << "Error! Centre index has exceeded total number of centres! ";
        std::cout << e << std::endl;
    }
    return centres[index];
}