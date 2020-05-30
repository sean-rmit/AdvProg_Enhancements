#include "Players.h"
#include <iostream>
#include <string>
#include <exception>

Players::Players(int numPlayers) {
    this->playersNum = numPlayers;
    players = new playerPtr[playersNum];
    for (int i = 0; i < numPlayers; i++)
    {
        Player *player = new Player();
        players[i] = player;
    }
}
Players::~Players() {
    for (int i = 0; i < playersNum; i++)
    {
        delete players[i];
    }
    delete players;
}

Players::Players(Players& other) {

}

int Players::getPlayersNum() {
    return playersNum;
}

playerPtr Players::getPlayer(int index) {
    try
    {
        if (index < 0 || index > playersNum-1)
        {
            throw "Out of Bounds Exception!";
        }
    }
    catch (char const *e)
    {
        std::cout << "Error! Index exceeded number of players! ";
        std::cout << e << std::endl;
    }
    return players[index];
}