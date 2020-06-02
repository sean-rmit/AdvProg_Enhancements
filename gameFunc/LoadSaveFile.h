#ifndef LoadSaveF
#define LoadSaveF

#include "pages.h"
#include <string>

class LoadSave {
public:

    LoadSave();
    ~LoadSave();

    // copy constructor
    LoadSave(LoadSave& other);

    // function to manage saving files
    void saveFile(std::string saveFile, Game *game, int currentPlayer);

    // function to manage loading files
    gamePtr loadFile(std::string loadFile, int &currentPlayer);

    // gets data from files during loading
    void getData(std::string line, std::string &data);

};

#endif 