// Warrior 战士类
#if !defined(WARRIOR_H)
#define WARRIOR_H

#include "../include/Enums.h"
#include <iostream>
// 定义战士类
class Warrior
{
protected:
    static WarriorType m_type;
    static int s_defaultLife[static_cast<int>(WarriorType::Count)]; // 默认生命值

    int m_life = 0;
    int m_number = 0;

public:
    // getter
    int getNumber() const
    {
        return this->m_number;
    }
    int getLife() const { return m_life; }
    static int getLifeCost(int index) { return s_defaultLife[index]; }
    WarriorType getType() const { return m_type; }
    // setter
    static void setDefaultLife(WarriorType type, int life)
    {
        s_defaultLife[static_cast<int>(type)] = life;
    }
    void setNumber(int number) { m_number = number; }
    // constructor && destructor
    Warrior();
    Warrior(WarriorType type);

    ~Warrior();
};

// 定义具体的战士类
class Dragon : public Warrior
{
public:
    Dragon() : Warrior(WarriorType::dragon) {}
};

class Ninja : public Warrior
{
public:
    Ninja() : Warrior(WarriorType::ninja) {}
};

class Iceman : public Warrior
{
public:
    Iceman() : Warrior(WarriorType::iceman) {}
};

class Lion : public Warrior
{
public:
    Lion() : Warrior(WarriorType::lion) {}
};

class Wolf : public Warrior
{
public:
    Wolf() : Warrior(WarriorType::wolf) {}
};

#endif // WARRIOR_H