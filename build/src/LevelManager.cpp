// LevelManager.cpp

#include "LevelManager.h"
#include "Registry.h"
#include "Level.h"
#include "LinuxUtils.h"

#include <unistd.h>
#include <cstring>
#include <iostream>
#include <thread>

void LevelManager::init(std::string levelDir)
{
    m_levelDir = levelDir;
    currentLevel = NULL;
}

bool LevelManager::heartbeat()
{
    if(!currentLevel)
    {
        currentLevel = &g_Reg.level;
        std::cout << "LevelManager::heartbeat | currentLevel->GetLevelID: " << std::to_string(g_Reg.level.GetLevelID()) << std::endl;
    }

    std::cout << "LevelManager::heartbeat currentLevelID: " << std::to_string(currentLevel->GetLevelID()) << std::endl;

    if(!currentLevel->launched())
    {
        if(LevelFilePresent(currentLevel->GetLevelID()))
        {
            int levelID = g_Reg.level.GetLevelID();
            std::cout << "LevelManager::heartbeat | DEBUG | Launching level " << levelID << std::endl;
            currentLevel->init(levelID, m_levelDir, GetStdoutFromCommand("tty | tr -d '\n'"));
            LaunchLevel(levelID);
        }
        else
        {
            std::cout << "LevelManager::heartbeat ERROR: Level " << currentLevel->GetLevelID() << " not found" << std::endl;
            return false;
        }

    }

    if(currentLevel->successful())
    {
        g_Reg.level.IncrementLevelID();
    }

    currentLevel->heartbeat();

    return true;
}

bool LevelManager::LaunchLevel(int levelID)
{
    std::string levelFile = GetLevelFile(levelID);
    if(currentLevel && levelFile != "NULL")
    {
        // std::thread thread(currentLevel->Launch(levelFile));
        currentLevel->Launch(levelFile);
        return true;
    }
    else
    {
        std::cout << "LevelManager::LaunchLevel(" << levelID << ") ERROR: Couldn't launch level with level file: " << levelFile << std::endl;
        return false;
    }
}

bool LevelManager::LevelFilePresent(int levelID)
{
    bool found = false;
    std::string levelNum("NULL");

    std::string cmd = "grep -r \"Level\" " + m_levelDir;
    std::istringstream lines(GetStdoutFromCommand(cmd));
    std::string line;

    while(std::getline(lines, line))
    {
        int pos;
        std::string keyword("Level\":");
        if((pos = line.find(keyword)) != std::string::npos)
        {
            levelNum = line.at(pos + keyword.size());
            if(std::stoi(levelNum) == levelID)
            {
                found = true;
                std::cout << "LevelManager::LevelFilePresent(" << levelID << ") | DEBUG | Level found: (actual)" << levelNum << "=(expected)" << levelID << std::endl;
                break;
            }
        }
    }

    return found;
}

std::string LevelManager::GetLevelFile(int levelID)
{
    std::string levelNum("NULL");
    std::string levelFile("NULL");

    std::string cmd = "find " + m_levelDir + " -name level" + std::to_string(levelID) + ".json" + " | tr -d '\n'";

    // TODO (BAR): Verify that this returned a valid pathname to a file
    return GetStdoutFromCommand(cmd);

}
