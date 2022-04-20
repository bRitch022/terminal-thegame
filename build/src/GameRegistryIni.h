// GameRegistryIni.h

#ifndef GAME_REG_H
#define GAME_REG_H

#include <string>
#include <fstream>
#include "inipp.h"

struct Game
{
    std::string version;
};

struct Player
{
    std::string name;
    int skillLevel;
};

struct Environment
{
    int stage;
    int level;
};

class GameRegistry {
public:
    GameRegistry(const std::string iniFile);
    ~GameRegistry() {}

    bool read();
    bool write();

    Game game;
    Player player;
    Environment environment;

private:
    const std::string m_iniFile;
    inipp::Ini<char> m_iniHandler;
    // std::ifstream *p_iniFile;
    std::ifstream f_iniFile;
};

#endif