// GameRegistryIni.cpp

#include <iostream>
#include "GameRegistryIni.h"

using namespace inipp;

GameRegistry::GameRegistry(const std::string iniFile) : m_iniFile(iniFile) 
{
    // TODO (BAR): Set game version from version.h
    read();
}

GameRegistry::~GameRegistry() 
{
    if(player) delete(player);
    if(engine) delete(engine);
}

/**
 * @brief Read the game registry
 * 
 * @todo Currently, this read the registry, but any updates made to it in
 * realtime do not propagate. In order to make the game "hackable", these
 * reads need to read in realtime. I thought just simply opening and closing 
 * the file would accomplish that, but alas it does not.
 * 
 * @return true for successful read
 * @return false if unsuccessful
 */
bool GameRegistry::read()
{
    bool success = true; // assume true for now

    std::ifstream f_iniFile(m_iniFile);
    if(!f_iniFile) 
    {
        std::cout << "ERROR: Cannot read " << m_iniFile << std::endl;
        return false; 
    }

    m_iniHandler.parse(f_iniFile);
    m_iniHandler.strip_trailing_comments();

    // Game
    get_value(m_iniHandler.sections["Game"], "version", game.version); 

    // Engine
    int engine_stage, engine_level;
    std::string engine_lastUserCommand;

    get_value(m_iniHandler.sections["Engine"], "stage", engine_stage);
    get_value(m_iniHandler.sections["Engine"], "level", engine_level);
    get_value(m_iniHandler.sections["Engine"], "last-command", engine_lastUserCommand); 

    if(!engine)
    {
        engine = new Engine();
    }
    engine->SetStage(engine_stage);
    engine->SetLevel(engine_level);
    if(engine_lastUserCommand == "")
    {
        engine_lastUserCommand = engine->GetLastUserCommand_FromBashHistory();
    }
    engine->SetLastCommand_FromRegistry(engine_lastUserCommand);

    // Player
    std::string player_name;
    int player_skillLevel;

    get_value(m_iniHandler.sections["Player"], "name", player_name);
    get_value(m_iniHandler.sections["Player"], "skill-level", player_skillLevel); 
    if(!player)
    {
        player = new Player(player_name);
    }
    player->SetSkillLevel(player_skillLevel);
    
#ifdef DEBUG
    system("clear");
    print();
#endif

    f_iniFile.close();

    return success;
}

/**
 * @brief Update the ini registry with in-game contents
 * Ideally, this is a RAM->ini swap with parameters that we
 * are interested in.
 * 
 * @return true 
 * @return false 
 */
bool GameRegistry::update()
{
// #ifdef DEBUG
//     std::ofstream f_iniFile(iniFile_new);
// #else
    std::ofstream f_iniFile(m_iniFile);
// #endif

    if(!f_iniFile) 
    {
// #ifdef DEBUG
//         std::cout << "ERROR: Couldn't open " << iniFile_new << " for writing" << std::endl;
// #else 
        std::cout << "ERROR: Couldn't open " << m_iniFile << " for writing" << std::endl; 
// #endif
        return false; 
    }

    f_iniFile << "; Game generated registry" << std::endl;
    f_iniFile << "[Game]" << std::endl;
    f_iniFile << "version=" << game.version << std::endl;
    f_iniFile << std::endl;

    if(player)
    {
        f_iniFile << "[Player]" << std::endl;
        f_iniFile << "name=" << player->GetName() << std::endl;
        f_iniFile << "skill-level=" << player->GetSkillLevel() << std::endl;
        f_iniFile << std::endl;
    }
    
    if(engine)
    {
        f_iniFile << "[Engine]" << std::endl;
        f_iniFile << "stage=" << engine->GetStage() << std::endl;
        f_iniFile << "level=" << engine->GetLevel() << std::endl;
        f_iniFile << "last-command=" << engine->GetLastUserCommand_FromBashHistory() << std::endl;
        f_iniFile << std::endl;
    }

    return true;
}

void GameRegistry::print()
{
    std::cout << "Game version: " << game.version << std::endl;
    if(engine)
    {
        std::cout << "Stage: " << engine->GetStage() << std::endl;
        std::cout << "Level: " << engine->GetLevel() << std::endl;
        std::cout << "Last Command: " << engine->GetLastUserCommand_FromRegistry() << std::endl; 
    }
    if(player)
    {
        std::cout << "Player name: " << player->GetName() << std::endl;   
        std::cout << "Player skill: " << player->GetSkillLevel() << std::endl;  
    }
}

void GameRegistry::printINI()
{
    m_iniHandler.generate(std::cout);
}