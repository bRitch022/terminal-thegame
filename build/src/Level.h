// Level.h

#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

struct scriptLine
{
    float typeWriterDelay;
    std::string msg;
    bool printed;
};

enum trigger_t { BASH_HISTORY };
enum trigger_action_t { PRINT };

struct actionTrigger
{
    trigger_t triggerType;
    std::string name;
    trigger_action_t triggerAction;
    std::string triggerMessage;
};

class Level {

public:
    Level(const std::string level_dir, const std::string out_pts);
    ~Level() {}

    int GetLevelID() { return m_levelID; }
    int GetTriggerNum() { return goal_triggers.size(); }
    int GetGrantedXP() { return m_grantedXP; }

private:
    bool ParseJSON(std::ifstream& j_file);
    bool DisplayMessage(std::string& msg);
    bool PrintNextScriptLine(std::vector<scriptLine>& script);

    int m_levelID;
    int m_grantedXP;

    std::vector<scriptLine> prelude_script;
    std::vector<scriptLine> interlude_script;
    std::vector<int> test;

    std::vector<actionTrigger> action_triggers;
    std::vector<std::string> goal_triggers;
    const std::string m_level_dir; // name of the directory where the level json files are stored
    const std::string m_out_pts; // name of the psuedo-terminal that the user is logged in on

};

#endif