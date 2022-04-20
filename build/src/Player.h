// Player.h

#ifndef PLAYER_H
#define PLAYER_H

#include <string> 

class Player {
public:
    Player(const std::string name) : m_name(name) {}
    ~Player() {}

    std::string GetName() { return m_name; }
    int GetSkillLevel() { return m_skillLevel; }
    void SetSkillLevel(int val) { m_skillLevel = val; }

private:
    const std::string m_name;
    int m_skillLevel;
};

#endif