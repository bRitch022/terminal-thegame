// level.h

#include <string>
#include <vector>

class Level {

public:
    uint8_t level;
    uint32_t xp_gained;

    typedef struct
    {
        float typeWriterDelay;
        std::string msg;
    } script_line;
    
    typedef enum trigger_t { COMMAND_LINE_INTERFACE, SOMESHIT };
    typedef enum trigger_action_t { PRINT };

    typedef struct
    {
        trigger_t triggerType;
        std::string name;
        trigger_action_t triggerAction;
    } actionTrigger;

    std::vector<script_line> prelude_script;
    std::vector<script_line> interlude_script;
    std::vector<actionTrigger> action_triggers;
    std::vector<std::string> goal_triggers;
    
};
