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
        // if(LevelFilePresent(currentLevel->GetLevelID()))
        if(LevelFilePresent(1))
        {
            int levelID = 1; // TODO (BAR): Remove this and uncomment next line
            // int levelID = g_Reg.level.GetLevelID();
            currentLevel->init(levelID, m_levelDir, GetStdoutFromCommand("tty | tr -d '\n'"));
            std::cout << "LevelManager::heartbeat Launching level " << levelID << std::endl;
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
            }
        }
    }

    return found;
}

std::string LevelManager::GetLevelFile(int levelID)
{
    std::string levelNum("NULL");
    std::string levelFile("NULL");

    std::string cmd = "ls " + m_levelDir;
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
                std::string json_keyword(".json:");
                if((pos = line.find(json_keyword)) != std::string::npos)
                {
                    levelFile = line.substr(0, (size_t)(pos + 4));
                }
            }
        }
    }

    return levelFile;
}
// /**
//  * @brief Main method for the LevelEngine
//  * This handles calling the correct Level files to display to the user
//  *
//  * @param argv This should include <dir>/Registry.ini
//  * @param argv This should include the source directory for level json files
//  * @return int
//  */
// int main(int argc, char** argv)
// {
//     // Check that there is referenced Registry.ini and Level source directory
//     if(argc <= 2)
//     {
//         std::cout << "Requires 2 arguments, only " << argc - 1 << " provided" << std::endl;
//         return -1;
//     }
//     else
//     {
//         if(strstr(argv[1], "Registry.ini") == NULL)
//         {
//             std::cout << "Missing argument: Registry.ini" << std::endl;
//             return -1;
//         }

//         if(strstr(argv[2], "/") == NULL)
//         {
//             std::cout << "Missing argument: Level source directory" << std::endl;
//             return -1;
//         }
//     }

//     // Otherwise, we have all the arguments we need
//     std::string registryFile = argv[1];
//     std::string levelSourceDirectory = argv[2];

//     // Initialize the game registry
//     Registry *p_registry = new Registry(registryFile);

//     Level *p_level = NULL;

//     // Main game loop
//     while(1)
//     {
//         // Read any changes that have been made to the registry
//         p_registry->read();

//         if(p_level == NULL)
//         {
//             switch(p_registry->EventManager->GetLevel())
//             {
//                 case 1:
//                     p_level = new Level("/" + levelSourceDirectory + "/level1.json");
//                     p_registry->level = p_level;
//                 break;

//                 default:
//                 break;
//             }
//         }
//         // Update ingame changes to the registry
//         p_registry->update();

//         usleep(1E5); // sleep for 100 msec
//     }

//     delete(p_registry);
//     return 0;
// }
