// Level.cpp

#include <fstream>
#include <iostream>
#include "LinuxUtils.h"
#include "Level.h"
#include "Registry.h"
#include "nlohmann/json.hpp"

extern Registry g_Reg;

using namespace nlohmann;

Level::Level()
{
    memset(m_current_state, 0, sizeof(m_current_state));
}
Level::~Level()
{
    if(m_current_state) delete(m_current_state);
}

bool Level::init(int levelID, std::string level_dir, std::string out_pts)
{
    m_levelID = levelID;
    m_level_dir = level_dir;
    m_out_pts = out_pts;
    // m_out_pts = "/dev/pts/0"; // TODO (BAR): Remove this, it's only temporary
    *m_current_state = START;

    return true;
}

/**
 * @brief
 * @todo Instead of Displaying message manually, send an EventRequest to the EventManager
 * For now, this is probably the quickest and most efficient way until there are
 * a lot of simultaneous events that need to be managed
 */
void Level::heartbeat()
{
    if(!g_Reg.GetKillSwitch())
    {
        switch(*m_current_state)
        {
            case START:
            case PRELUDE:
            {
                bool printed = false;
                std::cout << "Level::heartbeat prelude_script lines: " << prelude_script.size() << std::endl;
                // which script line needs printing?
                for(auto line : prelude_script)
                {
                    if(!line.printed)
                    {
                        std::cout << "Level::heartbeat Getting ready to print" << std::endl;
                        DisplayMessage(line.msg);
                        // TODO (BAR): // DisplayMsgWithTypewriter(line.msg, line.typeWriterDelay);
                        line.printed = true;
                        printed = true;
                    }
                }

                if(!printed) // no messages left to print
                {
                    // Transition to the next state
                    *m_current_state = RUNNING;
                }
            }
            break;
            case RUNNING:
                // check the action triggers
            break;

            case INTERLUDE:
            break;

            case EXIT:
            break;

        }
    }
    else
    {
        std::cout << "Level::heartbeat Killswitch signal -- shutting down" << std::endl;

        exit(0);
    }
}

bool Level::Launch(std::string levelFile)
{
    bool rc = false;

    std::ifstream f_levelFile(levelFile);

    if(!f_levelFile.is_open())
    {
        std::cout << "Level::heartbeat Couldn't open " << levelFile << std::endl;
        return rc;
    }

    if(ParseJSON(f_levelFile))
    {
        m_launched = true;
        rc = true;
    }

    return rc;
}

bool Level::ParseJSON(std::ifstream& j_file)
{
    bool rc = true;
    json j;
    j_file >> j;

    if(j.is_object())
    {
        if(j.contains("Level") && j["Level"].is_number_integer() && m_levelID != j["Level"])
        {
            std::cout << "Level::heartbeat JSON Level and levelID don't match" << std::endl;
            return false;
        }

        if(j.contains("XP-Gained") && j["XP-Gained"].is_number())
        {
            m_grantedXP = j["XP-Gained"];
        }

        if(j.contains("Prelude-Script") && j["Prelude-Script"].is_array())
        {
            struct scriptLine tmp;
            tmp.printed = false;
            for(size_t i = 0; i < j["Prelude-Script"].size(); i++)
            {
                if(j["Prelude-Script"][i].is_object() &&
                   j["Prelude-Script"][i].contains("TypewriterDelay") &&
                   j["Prelude-Script"][i]["TypewriterDelay"].is_number_float() &&
                   j["Prelude-Script"][i].contains("msg") &&
                   j["Prelude-Script"][i]["msg"].is_string())
                {
                    tmp.typeWriterDelay = j["Prelude-Script"][i]["TypewriterDelay"];
                    tmp.msg = j["Prelude-Script"][i]["msg"];
                    prelude_script.push_back(tmp);
                }
                else
                {
                    std::cout << "Level::heartbeatERROR:Scripts need to include both a TypewriterDelay and a msg" << std::endl;
                    rc = false;
                    continue;
                }
            }
        }

        if(j.contains("Action-Triggers") && j["Action-Triggers"].is_array())
        {
            struct actionTrigger tmp;
            for(size_t i = 0; i < j["Action-Triggers"].size(); i++)
            {
                if(j["Action-Triggers"][i].is_object() &&
                   j["Action-Triggers"][i].contains("TriggerType") &&
                   j["Action-Triggers"][i]["TriggerType"].is_string() &&
                   j["Action-Triggers"][i].contains("Name") &&
                   j["Action-Triggers"][i]["Name"].is_string() &&
                   j["Action-Triggers"][i].contains("TriggerAction") &&
                   j["Action-Triggers"][i]["TriggerAction"].is_string())
                {
                    tmp.name = j["Action-Triggers"][i]["Name"];
                    if(j["Action-Triggers"][i]["TriggerType"] == "BashHistory")
                    {
                        tmp.triggerType = BASH_HISTORY;
                    }
                    if(j["Action-Triggers"][i]["TriggerAction"] == "print")
                    {
                        if(j["Action-Triggers"][i].contains("TriggerMessage") &&
                           j["Action-Triggers"][i]["TriggerMessage"].is_string())
                        {
                            tmp.triggerAction = PRINT;
                            tmp.triggerMessage = j["Action-Triggers"][i]["TriggerMessage"];
                        }
                        else
                            std::cout << "Level::heartbeatERROR:Expected a TriggerMessage for a TriggerAction type of 'print'" << std::endl;
                            rc = false;
                            continue;
                    }
                }

                action_triggers.push_back(tmp);
            }
        }
        if(j.contains("Goal-Triggers") && j["Goal-Triggers"].is_array())
        {
            for(size_t i = 0; i < j["Goal-Triggers"].size(); i++)
            {
                if(j["Goal-Triggers"][i].is_string())
                {
                    goal_triggers.push_back(j["Goal-Triggers"][i]);
                }
            }
        }

        if(j.contains("Interlude-Script") && j["Interlude-Script"].is_array())
        {
            struct scriptLine tmp;
            tmp.printed = false;
            for(size_t i = 0; i < j["Interlude-Script"].size(); i++)
            {
                if(j["Interlude-Script"][i].is_object() &&
                   j["Interlude-Script"][i].contains("TypewriterDelay") &&
                   j["Interlude-Script"][i]["TypewriterDelay"].is_number_float() &&
                   j["Interlude-Script"][i].contains("msg") &&
                   j["Interlude-Script"][i]["msg"].is_string())
                {
                    tmp.typeWriterDelay = j["Interlude-Script"][i]["TypewriterDelay"];
                    tmp.msg = j["Interlude-Script"][i]["msg"];
                    interlude_script.push_back(tmp);
                }
                else
                {
                    std::cout << "Level::heartbeatERROR:Scripts need to include both a TypewriterDelay and a msg" << std::endl;
                    rc = false;
                    continue;
                }
            }
        }
     }
    else
    {
        std::cout << "Level::heartbeatERROR:JSON file does not contain an object" << std::endl;
        rc = false;
    }

    return rc;
}

/**
 * @brief Types a message to the user's terminal
 *
 * @param msg string The message to be displayed
 *
 * @return true
 * @return false
 */
bool Level::DisplayMessage(std::string& msg)
{
    std::string cmd = "echo \"" + msg + "\" > " + m_out_pts;
    if(system(cmd.c_str()))
    {
        return true;
    }

    return false;
}

bool Level::PrintNextScriptLine(std::vector<scriptLine>& script)
{
    bool rc = false;

    for (auto line : script)
    {
        if(line.printed)
        {
            continue;
        }
        else
        {
            DisplayMessage(line.msg);
            line.printed = true;
            rc = true;
            break;
        }
    }

    return rc;
}

// /**
//  * @brief This test is outdated (5/7/2022) TODO(BAR): Move this to Unit Testing
//  * @brief To start, call:
//  * Level <registry.ini location> <level directory> <output terminal>
//  *
//  * @todo Do we need some getopt parameter parsing? It's not user accessible, so probably not
//  *
//  * @param argc
//  * @param argv
//  * @return int
//  */
// int main(int argc, char** argv)
// {
//     if(argc <= 4)
//     {
//         std::cout << "ERROR: Must supply a registry.ini location, level directory location and output pseudo-terminal" << std::endl;
//         return -1;
//     }
//     std::string regDir = argv[1];
//     std::string levelDir = argv[2];
//     std::string out_pts = argv[3];

//     Level *p_level;
//     Registry p_registry(regDir);

//     int levelID = p_registry.level->GetLevelID();
//     if(checkForLevel(levelDir, levelID))
//     {
//         p_level = new Level(levelID, levelDir, GetStdoutFromCommand("tty"));
//     }
//     else
//     {
//         std::cout << "ERROR: Level file not found" << std::endl;
//         return -1;
//     }



// exit_main:
//     delete(p_level);
// }