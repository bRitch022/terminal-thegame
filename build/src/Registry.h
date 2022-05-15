// RegistryIni.h

#ifndef REG_H
#define REG_H

#include <string>
#include <fstream>
#include <iniparser.hpp>
#include "Player.h"
#include "EventManager.h"
#include "Level.h"

struct Game
{
    std::string version;
    int level;
    bool killswitch;
};

typedef enum
{
    GAME, ENGINE, PLAYER
} SECTION_T;

class Registry {
public:

    Registry() {}
    ~Registry() {}

    bool init(const std::string iniFile);
    bool heartbeat();
    bool read();
    bool update();
    void print();

    bool GetGameLevel() { return game.level; }
    bool GetKillSwitch() { return game.killswitch; }


    Game game;
    Player player;
    Level level;
    EventManager event_man;

private:
    std::string m_iniFile;
    INI::File m_iniHandler;
};

extern Registry g_Reg;

#endif