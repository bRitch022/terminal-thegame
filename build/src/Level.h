// Level.h

#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <fstream>

struct script_line
{
    float typeWriterDelay;
    std::string msg;
};

enum trigger_t { COMMAND_LINE_INTERFACE, SOMESHIT };
enum trigger_action_t { PRINT };

struct actionTrigger
{
    trigger_t triggerType;
    std::string name;
    trigger_action_t triggerAction;
};

class Level {

public:
    Level(std::string level_file) : m_levelFile(level_file) {}
    ~Level() {}

    int level;
    int xp_gained;

    std::vector<script_line> prelude_script;
    std::vector<script_line> interlude_script;
    std::vector<actionTrigger> action_triggers;
    std::vector<std::string> goal_triggers;

private:
    const std::string m_levelFile;

};

#endif