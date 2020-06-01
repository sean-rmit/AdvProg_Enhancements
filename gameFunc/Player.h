#ifndef GamePlayer
#define GamePlayer

#include "Mosaic.h"
#include "Factory.h"
#include "Centre.h"
#include "Line.h"
#include "utils.h"

class Player {
public:

    // Constructor
    Player(bool advMode, bool greyMode);
    // Deconstructor
    ~Player();

    std::string getPlayerName();
    void setPlayerName(std::string name);
    mosaicPtr getPlayerMosaic();
    void setPlayerMosaic(Mosaic *mosaic);
    int getPlayerScore();
    void setPlayerScore(int score);
    // add the score to player's total score
    void addToPlayerScore(int score);
    bool takeTilesFromFactory(Factory *factory, char colour, Centre *centre, int patternLineIndex, Lid *lid);
    bool takeTilesFromCentre(char colour, Centre *centre, int patternLineIndex, Lid *lid, bool &firstPlayerTokenTaken);
    bool takeTilesFromFactoryToBrokenLine(Factory *factory, char colour, Centre *centre, Lid *lid);
    bool takeTilesFromCentreToBrokenLine(Centre *centre, char colour, Lid *lid, bool &firstPlayerTokenTaken);
    void moveTilesFromPatternLineToWall(Lid *lid, bool greyMode);
    void moveTilesFromBrokenTilesToLid(Lid *lid);

    void addPenaltyPoints();
    void addEndGameBonusPoints();
    
private:
    std::string playerName;
    int playerScore;
    Mosaic *playerMosaic;
};

typedef Player* playerPtr;

#endif // GamePlayer