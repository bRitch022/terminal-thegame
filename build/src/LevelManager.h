// LevelManager.h

#include "Manager.h"
#include "Registry.h"

class LevelManager : public Manager("level")
{
public:
    LevelManager() {}
    ~LevelManager() {}

    bool RegistryPoll() override;
    bool RegistryPush() override;

private:
    bool LaunchLevel();
};