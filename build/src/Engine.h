// Engine.h

#ifndef ENGINE_H
#define ENGINE_H

#include <string>

class Engine
{
public:
    Engine() {}
    ~Engine() {}

    std::string GetLastUserCommand_FromBashHistory();
    
    int GetStage() { return m_stage; }
    int GetLevel() { return m_level; }
    std::string GetLastUserCommand_FromRegistry() { return m_lastUserCommand; }    

    void SetStage(int val) { m_stage = val; }
    void SetLevel(int val) { m_level = val; }
    void SetLastCommand_FromRegistry(std::string val);

private:
    int m_stage;
    int m_level;
    std::string m_lastUserCommand;
};

#endif