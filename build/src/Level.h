// Level.h

#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

enum levelState
{
    START, PRELUDE, RUNNING, INTERLUDE, EXIT
};

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
    Level();
    ~Level();

    bool init(int levelId, std::string level_dir, std::string out_pts);
    void heartbeat();

    bool Launch(std::string levelFile);
    void SetLevelID(int levelID) { m_levelID = levelID; }
    int GetLevelID() { return m_levelID; }
    int GetTriggerNum() { return goal_triggers.size(); }
    int GetGrantedXP() { return m_grantedXP; }

    void IncrementLevelID() { m_levelID++; } // TODO (BAR): Level validation
    bool launched() { return m_launched; }
    bool successful() { return m_successful; }

private:
    bool ParseJSON(std::ifstream& j_file);
    bool DisplayMessage(std::string& msg);
    bool PrintNextScriptLine(std::vector<scriptLine>& script);

    levelState m_current_state;

    int m_levelID;
    int m_grantedXP;

    int m_launched;   //< true: a level thread has been launched
    int m_successful; //< true: the player has completed all objectives of the level

    std::vector<scriptLine> prelude_script;
    std::vector<scriptLine> interlude_script;
    std::vector<int> test;

    std::vector<actionTrigger> action_triggers;
    std::vector<std::string> goal_triggers;
    std::string m_level_dir; //< name of the directory where the level json files are stored
    std::string m_out_pts; //< name of the psuedo-terminal that the user is logged in on

};

#endif