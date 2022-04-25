// EventManager.h

#ifndef BASH_ENGINE_H
#define BASH_ENGINE_H

#include <string>
#include "Manager.h"

class EventManager : public Manager("event")
{
public:
    EventManager() {}
    ~EventManager() {}

    std::string GetStdoutFromCommand(std::string cmd);
    std::string GetLastUserCommand_FromBashHistory();
    std::string GetLastUserCommand_FromRegistry() { return m_lastUserCommand; }
    void SetLastCommand_FromRegistry(std::string val);

private:
    int m_stage;
    int m_level;
    std::string m_lastUserCommand;
};

#endif