// GameRegistryIni.cpp

#include <iostream>
#include "GameRegistryIni.h"

// using namespace inipp;

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
 * @return true for successful read
 * @return false if unsuccessful
 */
bool GameRegistry::read()
{
    bool success = true; // assume true for now

    if(!m_iniHandler.Load(m_iniFile))
    {
        std::ifstream f_iniFile(m_iniFile);
        if(!f_iniFile.is_open())
        {
            std::cout << "ERROR: Cannot read " << m_iniFile << std::endl;
            return false;
        }

        f_iniFile >> m_iniHandler;
    }

    std::cout << "ini [Game:version]: " << m_iniHandler.GetSection("Game")->GetValue("version").AsString() << std::endl;
    std::cout << "game.version: " << game.version << std::endl;

    // Game
    game.version = m_iniHandler.GetSection("Game")->GetValue("version").AsString();

    // Engine
    int engine_stage, engine_level;
    std::string engine_lastUserCommand;

    engine_stage = m_iniHandler.GetSection("Engine")->GetValue("stage").AsInt();
    engine_level = m_iniHandler.GetSection("Engine")->GetValue("level").AsInt();
    engine_lastUserCommand = m_iniHandler.GetSection("Engine")->GetValue("last-command").AsString();

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
    int player_skillLevel, player_XP;

    player_name = m_iniHandler.GetSection("Player")->GetValue("name").AsString();
    player_skillLevel = m_iniHandler.GetSection("Player")->GetValue("skill-level").AsInt();
    player_XP = m_iniHandler.GetSection("Player")->GetValue("XP").AsInt();
    if(!player)
    {
        player = new Player(player_name);
    }
    player->SetSkillLevel(player_skillLevel);
    player->SetXP(player_XP);

#ifdef DEBUG
    system("clear");
    print();
#endif

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
    if(!m_iniHandler.Load(m_iniFile))
    {
        std::ofstream f_iniFile(m_iniFile);
        if(!f_iniFile.is_open())
        {
            std::cout << "ERROR: Cannot read " << m_iniFile << std::endl;
            return false;
        }

        f_iniFile << m_iniHandler;
    }

    m_iniHandler.GetSection("Game")->SetValue("version", game.version);

    if(player)
    {
        m_iniHandler.GetSection("Player")->SetValue("name", player->GetName());
        m_iniHandler.GetSection("Player")->SetValue("skill-level", player->GetSkillLevel());
        m_iniHandler.GetSection("Player")->SetValue("XP", player->GetXP());
    }

    if(engine)
    {
        m_iniHandler.GetSection("Engine")->SetValue("stage", engine->GetStage());
        m_iniHandler.GetSection("Engine")->SetValue("level", engine->GetLevel());
        m_iniHandler.GetSection("Engine")->SetValue("last-command", engine->GetLastUserCommand_FromBashHistory());
    }

    m_iniHandler.Save(m_iniFile);

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
        std::cout << "Player XP: " << player->GetXP() << std::endl;
    }
}

void GameRegistry::printINI()
{
    // m_iniHandler.generate(std::cout);
}