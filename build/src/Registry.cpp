// RegistryIni.cpp

#include <iostream>
#include "Registry.h"

bool Registry::init(const std::string iniFile)
{
    // TODO (BAR): Set game version from version.h
    m_iniFile = iniFile;
    memset(&game, 0, sizeof(game));
    memset(&player, 0, sizeof(player));
    memset(&level, 0, sizeof(level));

    bool rc = read();
    rc ? std::cout << "Registry::init(" << iniFile << ") | Registry Initialized" << std::endl : std::cout << "Registry Initialize Failure" << std::endl;
    return rc; 
}

/**
 * @brief
 * @todo @BAR
 *
 * @return true
 * @return false
 */
bool Registry::heartbeat()
{
    std::cout << "Registry Level ID: " << g_Reg.GetGameLevel() << std::endl;
    std::cout << "Registry Level ID: " << g_Reg.level.GetLevelID() << std::endl;
    return true;
}

/**
 * @brief Read the game registry
 * @param section SECTION_T
 * Specify a section type to read only that section
 *
 * @return true for successful read
 * @return false if unsuccessful
 */
bool Registry::read()
{
    bool success = true; // assume true for now

    if(!m_iniHandler.Load(m_iniFile))
    {
        std::ifstream f_iniFile(m_iniFile);
        if(!f_iniFile.is_open())
        {
            std::cout << "Registry::read | ERROR: Cannot read " << m_iniFile << std::endl;
            return false;
        }

        f_iniFile >> m_iniHandler;
    }
    std::string version = m_iniHandler.GetSection("Game")->GetValue("version").AsString();
    game.version = version;
    game.level = m_iniHandler.GetSection("Game")->GetValue("level").AsInt();
    game.killswitch = m_iniHandler.GetSection("Game")->GetValue("killswitch").AsBool();

    std::string engine_lastUserCommand = m_iniHandler.GetSection("Events")->GetValue("last-command").AsString();

    if(engine_lastUserCommand == "")
    {
        engine_lastUserCommand = event_man.GetLastUserCommand_FromBashHistory();
    }
    event_man.SetLastCommand_FromRegistry(engine_lastUserCommand);

    std::string player_name;
    int player_skillLevel, player_XP;

    player_name = m_iniHandler.GetSection("Player")->GetValue("name").AsString();
    player_skillLevel = m_iniHandler.GetSection("Player")->GetValue("skill-level").AsInt();
    player_XP = m_iniHandler.GetSection("Player")->GetValue("XP").AsInt();

    player.SetName(player_name);
    player.SetSkillLevel(player_skillLevel);
    player.SetXP(player_XP);

#ifdef DEBUG
    // system("clear");
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
bool Registry::update()
{
    if(!m_iniHandler.Load(m_iniFile))
    {
        std::ofstream f_iniFile(m_iniFile);
        if(!f_iniFile.is_open())
        {
            std::cout << "Registry::update | ERROR: Cannot read " << m_iniFile << std::endl;
            return false;
        }

        f_iniFile << m_iniHandler;
    }

    m_iniHandler.GetSection("Game")->SetValue("version", game.version);
    m_iniHandler.GetSection("Game")->SetValue("level", game.level);

    m_iniHandler.GetSection("Engine")->SetValue("last-command", event_man.GetLastUserCommand_FromBashHistory());

    m_iniHandler.GetSection("Player")->SetValue("name", player.GetName());
    m_iniHandler.GetSection("Player")->SetValue("skill-level", player.GetSkillLevel());
    m_iniHandler.GetSection("Player")->SetValue("XP", player.GetXP());


    m_iniHandler.Save(m_iniFile);

    return true;
}

void Registry::print()
{
    std::cout << "Game version: " << game.version << std::endl;
    std::cout << "Level: " << game.level << std::endl;
    std::cout << "Killswitch: " << game.killswitch << std::endl;

    std::cout << "Last Command: " << event_man.GetLastUserCommand_FromRegistry() << std::endl;

    std::cout << "Player name: " << player.GetName() << std::endl;
    std::cout << "Player skill: " << player.GetSkillLevel() << std::endl;
    std::cout << "Player XP: " << player.GetXP() << std::endl;

}
