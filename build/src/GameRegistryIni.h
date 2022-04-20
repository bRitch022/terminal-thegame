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

// For tracking the command line
struct CLI
{
    std::string lastCommand;
};

class GameRegistry {
public:
    GameRegistry(const std::string iniFile);
    ~GameRegistry() {}

    bool read();
    bool update();
    void print();
    void printINI();

    Game game;
    Player player;
    Environment environment;
    CLI cli;

private:
    const std::string m_iniFile;
    inipp::Ini<char> m_iniHandler;
#ifdef DEBUG
    const char* iniFile_new = "../game/gamefiles/GameRegistryNew.ini"; // (BAR): This is for testing purposes so we don't overwrite the current registry file
#endif
};

#endif