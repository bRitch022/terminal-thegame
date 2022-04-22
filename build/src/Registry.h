// RegistryIni.h

#ifndef GAME_REG_H
#define GAME_REG_H

#include <string>
#include <fstream>
#include <iniparser.hpp>
#include "Player.h"
#include "Event.h"
#include "Level.h"

struct Game
{
    std::string version;
};

class Registry {
public:
    Registry(const std::string iniFile);
    ~Registry();

    bool read();
    bool update();
    bool print();

    Player *player;
    Event *events;
    Level *level;

private:
    const std::string m_iniFile;
    INI::File m_iniHandler;
};

#endif