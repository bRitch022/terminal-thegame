// stage.h

#include <string>
#include <vector>
#include "level.h"

class Stage {
public:
    std::string title;
    uint8_t stage_no;
    std::vector<Level> levels;
};
