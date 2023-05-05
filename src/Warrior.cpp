// src\Warrior.cpp 战士类的实现

#include "../include/Warrior.h"
#include "../include/Enums.h"
#include "../include/WeaponFactory.h"
// 初始化战士的默认生命值 全部为0 ，防止调用时出错

WarriorType Warrior::m_type = WarriorType::dragon;
int Warrior::s_defaultLife[static_cast<int>(WarriorType::Count)] = { 0 };

void Warrior::addWeapon(WeaponType type, int attack, int number)
{
    auto weapon = WeaponFactory::createWeapon(type);
    weapon->setNumber(number);
    weapons.emplace_back(std::move(weapon));
}

Warrior::Warrior()
{
    // 示例输出 000 red iceman 1 born with strength 5,1 iceman in red headquarter
    this->m_type = WarriorType::dragon;
    this->m_number = 1;
    this->m_life = 5;
}

Warrior::Warrior(WarriorType type, int number)
{
    m_type = type;
    this->m_life = s_defaultLife[static_cast<int>(type)];
    this->m_number = number;
}

Warrior::~Warrior()
{
}
