// GameRegistryIni.h

#ifndef GAME_REG_H
#define GAME_REG_H

#include <string>
#include <fstream>
#include <iniparser.hpp>
#include "Player.h"
#include "BASHEngine.h"
#include "Level.h"

struct Game
{
    std::string version;
};

class GameRegistry {
public:
    GameRegistry(const std::string iniFile);
    ~GameRegistry();

    bool read();
    bool update();
    void print();
    void printINI();

    Game game;
    Player *player;
    BASHEngine *BASHengine;
    Level *level;

private:
    const std::string m_iniFile;
    INI::File m_iniHandler;
};

#endif