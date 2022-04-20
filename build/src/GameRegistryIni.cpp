// GameRegistryIni.cpp

#include "GameRegistryIni.h"
#include <iostream>

using namespace inipp;

GameRegistry::GameRegistry(const std::string iniFile) : m_iniFile(iniFile) 
{
    // TODO (BAR): Set game version from version.h
    read();
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

    std::ifstream f_iniFile(m_iniFile.c_str());

    m_iniHandler.parse(f_iniFile);
    m_iniHandler.strip_trailing_comments();

    success = get_value(m_iniHandler.sections["Game"], "version", game.version); 

    if(success) success = get_value(m_iniHandler.sections["Environment"], "stage", environment.stage);
    else std::cout << "Parse error" << std::endl;

    if(success) success = get_value(m_iniHandler.sections["Environment"], "level", environment.level);
    else std::cout << "Parse error" << std::endl;

    if(success) success = get_value(m_iniHandler.sections["Player"], "name", player.name);
    else std::cout << "Parse error" << std::endl;

    if(success) success = get_value(m_iniHandler.sections["Player"], "skill-level", player.skillLevel); 
    else std::cout << "Parse error" << std::endl;
    
    if(success) success = get_value(m_iniHandler.sections["CLI"], "last-command", cli.lastCommand); 
    else std::cout << "Parse error" << std::endl;
   

#ifdef DEBUG
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
#ifndef DEBUG
    std::ofstream f_iniFile(m_iniFile);
#else
    std::ofstream f_iniFile(iniFile_new);
#endif

    if(!f_iniFile) { return false; }

    f_iniFile << "; Game generated registry" << std::endl;
    f_iniFile << "[Game]" << std::endl;
    f_iniFile << "version=" << game.version << std::endl;
    f_iniFile << std::endl;

    f_iniFile << "[Player]" << std::endl;
    f_iniFile << "name=" << player.name << std::endl;
    f_iniFile << "skill-level=" << player.skillLevel << std::endl;
    f_iniFile << std::endl;
    
    f_iniFile << "[Environment]" << std::endl;
    f_iniFile << "stage=" << environment.stage << std::endl;
    f_iniFile << "level=" << environment.level << std::endl;
    f_iniFile << std::endl;

    f_iniFile << "[CLI]" << std::endl;
    f_iniFile << "last-command=" << cli.lastCommand << std::endl;
    f_iniFile << std::endl;

    return true;
}

void GameRegistry::print()
{
    std::cout << "Game version: " << game.version << std::endl;
    std::cout << "Stage: " << environment.stage << std::endl;
    std::cout << "Level: " << environment.level << std::endl;
    std::cout << "Player name: " << player.name << std::endl;   
    std::cout << "Player skill: " << player.skillLevel << std::endl;  
    std::cout << "Last Command: " << cli.lastCommand << std::endl; 
}

void GameRegistry::printINI()
{
    m_iniHandler.generate(std::cout);
}