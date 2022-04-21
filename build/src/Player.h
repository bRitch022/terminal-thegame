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
    int GetXP() { return m_XP; }

    void SetSkillLevel(int val) { m_skillLevel = val; }
    void SetXP(int val) { m_XP = val; }
    void AddXP(int val) { m_XP += val; }

private:
    const std::string m_name;
    int m_skillLevel;
    int m_XP;
};

#endif