// Level.cpp

#include <fstream>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <cstdio>

#include "LinuxUtils.h"
#include "Level.h"
#include "Registry.h"

#include "nlohmann/json.hpp"

using namespace nlohmann;

bool Level::init(int levelID, std::string level_dir, std::string out_pts)
{
    m_levelID = levelID;
    m_level_dir = level_dir;
    m_out_pts = out_pts;
    m_current_state = START;

    return true;
}

/**
 * @brief
 * @todo Instead of Displaying message manually, send an EventRequest to the EventManager
 * For now though, this is probably the quickest and most efficient way until there are
 * a lot of simultaneous events that need to be managed
 */
void Level::heartbeat()
{
    if(!g_Reg.GetKillSwitch())
    {
        switch(m_current_state)
        {
            case START:
            case PRELUDE:
            {
                bool printed = false;
                std::cout << "Level::heartbeat | DEBUG | prelude_script lines: " << prelude_script.size() << std::endl;
                // which script line needs printing?

                printed = PrintNextScriptLine(prelude_script);

                if(!printed) // no messages left to print
                {
                    // Transition to the next state
                    m_current_state = RUNNING;
                }
            }
            break;
            case RUNNING:
                // TODO (BAR): check the action triggers
                m_current_state = INTERLUDE;
            break;

            case INTERLUDE:
                m_current_state = EXIT;
            break;

            case EXIT:
            break;

        }
    }
    else
    {
        std::cout << "Level::heartbeat Killswitch signal -- shutting down" << std::endl;

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
 * @brief Types a message to the players terminal
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

/**
 * @brief Display a message to the player terminal with a character delay
 * This simulates the text being typed in realtime
 *
 * @param msg
 * @param typeWriterDelay
 * @return true
 * @return false
 */
bool Level::DisplayMsgWithTypewriter(std::string msg, float typeWriterDelay)
{
    const long delay = (typeWriterDelay * 1E6);

    std::ostringstream cmd;

    int i = 0;
    while(msg[i] != '\0')
    {
        if(msg[i] == ' ')
        {
            cmd << "echo -n \" \" > " << m_out_pts << std::endl;
            i++;
        }
        else if(msg[i] == '\"') // TODO (BAR): Fix this, doesn't print quotes
        {
            cmd << "echo -n \\"" > " << m_out_pts << std::endl;
            i++;
        }
        else
        {
            cmd << "echo -n " << msg[i++] << " > " << m_out_pts << std::endl;
        }

        system(cmd.str().c_str());

        usleep(delay);

        cmd.str("");
        cmd.clear();
    }

    std::cout << std::endl;

    return true;
}

bool Level::PrintNextScriptLine(std::vector<scriptLine>& script)
{
    bool rc = false;

    for (auto& line : script)
    {
        if(line.printed)
        {
            continue;
        }
        else
        {
            DisplayMsgWithTypewriter(line.msg, line.typeWriterDelay);
            line.printed = true;
            rc = true;
            break;
        }
    }

    return rc;
}