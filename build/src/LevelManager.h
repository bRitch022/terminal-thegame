// LevelManager.h

#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

// #include "Manager.h"
#include "Registry.h"

// class LevelManager : public Manager
class LevelManager
{
public:
    // LevelManager() : Manager("level") {}
    LevelManager() {}
    ~LevelManager() {}

    // bool RegistryPoll() override;
    // bool RegistryPush() override;

    void init(std::string levelDir);
    bool heartbeat();

private:
    bool LaunchLevel(int levelID);
    bool LevelFilePresent(int levelID);
    std::string GetLevelFile(int levelID);

    Level *currentLevel;

    std::string m_levelDir;
    std::vector<std::string> m_commands;
};

#endif