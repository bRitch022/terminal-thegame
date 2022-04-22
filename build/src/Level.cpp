// Level.cpp

#include <fstream>
#include <iostream>
#include "Level.h"
#include "nlohmann/json.hpp"

using namespace nlohmann;

bool Level::ParseJSON(std::ifstream j_file)
{
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

        // TODO (BAR): Finish the rest
    }
    else
    {
        std::cout << "JSON file does not contain an object" << std::endl;
    }
}
bool Level::DisplayMessage()
{

}