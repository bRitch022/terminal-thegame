// GameRegistryIni.h

#ifndef GAME_REG_H
#define GAME_REG_H

#include <string>
#include <fstream>
#include "inipp.h"
#include "Player.h"
#include "Engine.h"

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
    Engine *engine;

private:
    const std::string m_iniFile;
    inipp::Ini<char> m_iniHandler;
#ifdef DEBUG
    const char* iniFile_new = "../game/gamefiles/GameRegistryNew.ini"; // (BAR): This is for testing purposes so we don't overwrite the current registry file
#endif
};

#endif