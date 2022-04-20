// GameRegistryIni.cpp

#include "GameRegistryIni.h"
#include <iostream>

using namespace inipp;

GameRegistry::GameRegistry(const std::string iniFile) : m_iniFile(iniFile) 
{
    read();
}

bool GameRegistry::read()
{
    bool success = true; // assume true for now

    // 'new' every time we read so that we can read updates
    // p_iniFile = new std::ifstream(m_iniFile.c_str());
    f_iniFile.open(m_iniFile.c_str());
    
    m_iniHandler.parse(f_iniFile);
    m_iniHandler.strip_trailing_comments();

    success = get_value(m_iniHandler.sections["Game"], "version", game.version); 

    if(success) get_value(m_iniHandler.sections["Environment"], "stage", environment.stage);
    else std::cout << "Parse error" << std::endl;

    if(success) get_value(m_iniHandler.sections["Environment"], "level", environment.level);
    else std::cout << "Parse error" << std::endl;

    if(success) get_value(m_iniHandler.sections["Player"], "name", player.name);
    else std::cout << "Parse error" << std::endl;

    if(success) get_value(m_iniHandler.sections["Player"], "skill-level", player.skillLevel); 
    else std::cout << "Parse error" << std::endl;

#ifdef DEBUG
    std::cout << "Game version: " << game.version << std::endl;
    std::cout << "Stage: " << environment.stage << std::endl;
    std::cout << "Level: " << environment.level << std::endl;
    std::cout << "Player name: " << player.name << std::endl;   
    std::cout << "Player skill: " << player.skillLevel << std::endl;   
#endif

    // Free the memory
    // delete(p_iniFile);

    return success;
}

bool GameRegistry::write()
{
    return true;
}
