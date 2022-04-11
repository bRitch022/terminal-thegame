/**
 * @file command.h
 * @brief Contains the architecture for a Command class
 * @copyright 
 * Copyright 2022, Ridgetech, LLC.. This software and its contents are 
 * Ridgetech confidental and proprietary. It cannot be used, disclosed 
 * or distributed without Ridgetech's prior written permission. Modification 
 * of this software is only allowed at the direction of Ridgetech.
 * All allowed modifications must be provided back to Ridgetech.
 */

#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>

using namespace std;

class LinuxCommand
{
public:
    LinuxCommand(string callname);

    typedef struct 
    {
        string short_option;
        string long_option;
        string option_text;

    } option;

    string GetCallName();
    option* GetOption(string& short_option);
    string GetHelpText();

    int SetOptions(vector<option>& options);
    void SetHelpText(const char* helptext);

private:
    const string    callname;
    vector<option>  options;
    string          helptext;
};

#endif