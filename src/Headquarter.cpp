// src\Headquarter.cpp 司令部类的实现

#include <array>
#include <iostream>
#include <iomanip>
#include <string>

#include "../include/Headquarter.h"
#include "../include/Warrior.h"
#include "../include/WarriorFactory.h"

int Headquarter::m_defaultLife = 0;

// 设置红色司令部生成战士的顺序
constexpr std::array<WarriorType, 5> warrior_order_red =
    {
        WarriorType::iceman,
        WarriorType::lion,
        WarriorType::wolf,
        WarriorType::ninja,
        WarriorType::dragon};

constexpr std::array<WarriorType, 5> warrior_order_blue =
    {
        WarriorType::lion,
        WarriorType::dragon,
        WarriorType::ninja,
        WarriorType::iceman,
        WarriorType::wolf};

bool Headquarter::createWarrior()
{
    const auto &warrior_order = (Headquarter::getColor() == head_color::red) ? warrior_order_red : warrior_order_blue;

    std::string output_color = (this->m_color == head_color::red) ? "red " : "blue ";

    auto &index = warrior_order[m_totalWarriors];

    if (isAbleToCreate(static_cast<int>(index)))
    {
        auto warrior = WarriorFactory::createWarrior(index);
        warrior->setNumber(m_totalWarriors + 1);

        int warrior_inedx = static_cast<int>(warrior->getType());
        std::string warrior_temp_type = warrior_type_name[warrior_inedx];

        int output_warrior_count = ++this->m_warriors_count[warrior_inedx];
        // fix it later
        std::cout << std::setw(3) << std::setfill('0') << m_totalWarriors << ' '
                  << output_color << warrior_temp_type << " " << warrior->getNumber()
                  << " born with strength " << warrior->getLife()
                  << "," << output_warrior_count << " " << warrior_temp_type
                  << " in "
                  << output_color << "headquarter"
                  << std::endl;

        // 000 red iceman 1 born with strength 5,1 iceman in red headquarter

        this->m_totalWarriors++;
        this->setLifeViaCost(warrior->getLife());
        m_warriors.emplace_back(std::move(warrior)); // 将 warrior 插入到 Headquarter 的容器中
    }
    else
    {

        std::cout << std::setw(3) << std::setfill('0') << m_totalWarriors << ' '
                  << output_color
                  << "headquarter stops making warriors"
                  << std::endl;
        return false;
    }

    return true;
}

bool Headquarter::isAbleToCreate(int warrior_index)
{
    return (this->getLife() - Warrior::getLifeCost(warrior_index)) < 0 ? false : true;
}

Headquarter::Headquarter()
{
    this->m_life = 0;
    this->m_color = head_color::red;
}

Headquarter::Headquarter(int life, head_color color)
{
    this->m_life = life;
    this->m_color = color;
}
