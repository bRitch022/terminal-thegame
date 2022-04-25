// Level.cpp

#include <fstream>
#include <iostream>
#include "Level.h"
#include "nlohmann/json.hpp"

using namespace nlohmann;

Level::Level(const std::string level_dir, const std::string out_pts) : m_level_dir(level_dir), m_out_pts(out_pts) {}

bool Level::ParseJSON(std::ifstream& j_file)
{
    bool rc = true;
    json j;
    j_file >> j;

    if(j.is_object())
    {
        if(j.contains("Level") && j["Level"].is_number_integer() && m_levelID != j["Level"])
        {
            std::cout << "JSON Level and levelID don't match" << std::endl;
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
                    std::cout << "ERROR:Scripts need to include both a TypewriterDelay and a msg" << std::endl;
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
                            std::cout << "ERROR:Expected a TriggerMessage for a TriggerAction type of 'print'" << std::endl;
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
                    std::cout << "ERROR:Scripts need to include both a TypewriterDelay and a msg" << std::endl;
                    rc = false;
                    continue;
                }
            }
        }
     }
    else
    {
        std::cout << "ERROR:JSON file does not contain an object" << std::endl;
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

