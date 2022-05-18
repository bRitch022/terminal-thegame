// Player.h

#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:
    Player() {}
    ~Player() {}

    std::string GetName() { return m_name; }
    int GetSkillLevel() { return m_skillLevel; }
    int GetXP() { return m_XP; }

    void SetName(std::string name) { m_name = name; }
    void SetSkillLevel(int val) { m_skillLevel = val; }
    void SetXP(int val) { m_XP = val; }
    void AddXP(int val) { m_XP += val; }

private:
    std::string m_name;
    int m_skillLevel;
    int m_XP;
};

#endif