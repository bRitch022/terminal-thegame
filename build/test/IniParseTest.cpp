// IniParseTest.cpp

#include <string>
#include <iostream>
#include <fstream>
#include "inipp.h"

using namespace std;

int main(int argc, char **argv)
{
    // Check that there is a file argument
    if(argc <= 1)
    {
        cout << "Missing argument: ini file" << endl;
        return -1;
    } 

    // Create ini handler
    inipp::Ini<char> iniHandler;

    // Create file handler
    ifstream iniFile(argv[1]);

    // Parse with ini handler
    iniHandler.parse(iniFile);

#if DEBUG
    // Print raw ini file contents
    cout << "Raw ini file: " << endl;
    iniHandler.generate(cout);
#endif

    // Massage the results
    iniHandler.strip_trailing_comments();
    // iniHandler.default_section(iniHandler.sections["Game"]);
    // iniHandler.interpolate();

#if DEBUG
    // Print massaged results
    cout << "Default section and interpolated ini file: " << endl;
    iniHandler.generate(cout);
#endif

    // Parse results
    std::string gameVersion;
    int stage;
    int level;
    std::string player_name;
    std::string player_skillLevel;
    std::string cli_lastCommand;

    inipp::get_value(iniHandler.sections["Game"], "version", gameVersion);
    inipp::get_value(iniHandler.sections["Environment"], "stage", stage);
    inipp::get_value(iniHandler.sections["Environment"], "level", level);
    inipp::get_value(iniHandler.sections["Player"], "name", player_name);
    inipp::get_value(iniHandler.sections["Player"], "skill-level", player_skillLevel);
    inipp::get_value(iniHandler.sections["CLI"], "last-command", cli_lastCommand);

    // Print parsed Ini contents
    cout << "Game version: " << gameVersion << endl;
    cout << "Stage: " << stage << endl;
    cout << "Level: " << level << endl;
    cout << "Player name: " << player_name << endl;   
    cout << "Player skill: " << player_skillLevel << endl;   
    cout << "Last Command: " << cli_lastCommand << endl;   

    return 0;
}