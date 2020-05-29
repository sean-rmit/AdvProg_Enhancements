#ifndef GamePlayers
#define GamePlayers

#include "Player.h"

class Players {
public:

    // Constructor
    Players(int numPlayers);
    // Deconstructor
    ~Players();

    // copy constructor
    Players(Players& other);
    // get player object at given index
    playerPtr getPlayer(int index);

    int getPlayersNum();

private:
    playerPtr *players;
    int playersNum;
};

typedef Players* playersPtr;

#endif // Game Players