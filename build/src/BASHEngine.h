// BASHEngine.h

#ifndef BASH_ENGINE_H
#define BASH_ENGINE_H

#include <string>

class BASHEngine
{
public:
    BASHEngine() {}
    ~BASHEngine() {}

    std::string GetStdoutFromCommand(std::string cmd);
    std::string GetLastUserCommand_FromBashHistory();
    std::string GetLastUserCommand_FromRegistry() { return m_lastUserCommand; }
    void SetLastCommand_FromRegistry(std::string val);

    int GetStage() { return m_stage; }
    int GetLevel() { return m_level; }

    void SetStage(int val) { m_stage = val; }
    void SetLevel(int val) { m_level = val; }

private:
    int m_stage;
    int m_level;
    std::string m_lastUserCommand;
};

#endif