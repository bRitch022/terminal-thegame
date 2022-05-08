// EventManager.h

#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <string>
// #include "Manager.h"

// class EventManager : public Manager // TODO (BAR)
class EventManager
{
public:
    EventManager() {}
    ~EventManager() {}

    std::string GetLastUserCommand_FromBashHistory();
    std::string GetLastUserCommand_FromRegistry() { return m_lastUserCommand; }
    void SetLastCommand_FromRegistry(std::string val);

    // bool RegistryPoll() override;
    // bool RegistryPush() override;

    bool heartbeat();

private:
    int m_stage;
    int m_level;
    std::string m_lastUserCommand;
};

#endif