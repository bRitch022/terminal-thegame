/**
 * @file command.cpp
 * @brief Contains the architecture for a Command class
 * @copyright 
 * Copyright 2022, Ridgetech, LLC.. This software and its contents are 
 * Ridgetech confidental and proprietary. It cannot be used, disclosed 
 * or distributed without Ridgetech's prior written permission. Modification 
 * of this software is only allowed at the direction of Ridgetech.
 * All allowed modifications must be provided back to Ridgetech.
 */

#include "command.h"

LinuxCommand::LinuxCommand(string _callname) : callname(_callname) {}

string LinuxCommand::GetCallName() 
{ 
    return callname; 
}

LinuxCommand::option* LinuxCommand::GetOption(string& short_option) 
{
    option *p_opt = nullptr;
    for(auto opt : options)
    {
        if(opt.short_option.find(short_option) != string::npos)
        {
            p_opt = &opt;
        }
    }

    return p_opt;
}

string LinuxCommand::GetHelpText() 
{ 
    return helptext; 
}

int LinuxCommand::SetOptions(vector<LinuxCommand::option>& _options)
{
    options = _options;
}
void LinuxCommand::SetHelpText(const char* _helptext)
{
    helptext = std::string(_helptext);
}
