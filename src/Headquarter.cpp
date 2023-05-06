// src\Headquarter.cpp 司令部类的实现

#include <array>
#include <iomanip>
#include <iostream>
#include <string>

#include "../include/Headquarter.h"
#include "../include/Warrior.h"
#include "../include/WarriorFactory.h"
#include "../include/Weapon.h"

int Headquarter::m_defaultLife = 0;

// 设置红色司令部生成战士的顺序
constexpr std::array<WarriorType, 5> warrior_order_red = {
    WarriorType::iceman,
    WarriorType::lion,
    WarriorType::wolf,
    WarriorType::ninja,
    WarriorType::dragon
};

constexpr std::array<WarriorType, 5> warrior_order_blue = {
    WarriorType::lion,
    WarriorType::dragon,
    WarriorType::ninja,
    WarriorType::iceman,
    WarriorType::wolf
};

bool Headquarter::createWarrior()
{
    const auto& warrior_order = (Headquarter::getColor() == head_color::red) ? warrior_order_red : warrior_order_blue;

    auto& index = warrior_order[m_totalWarriors];

    if (isAbleToCreate(static_cast<int>(index))) {
        auto warrior = WarriorFactory::createWarrior(index, m_totalWarriors + 1);

        int warrior_inedx = static_cast<int>(warrior->getType());

        // 对Headquarter的成员变量进行修改
        this->m_totalWarriors++;
        this->m_warriors_count[warrior_inedx]++;
        this->setLifeViaCost(warrior->getHP());
        // fix it later

        // 输出 log 信息
        // Print info about the current warrior
        std::cout << std::setw(3) << std::setfill('0') << m_totalWarriors - 1 << ' '
                  << this->getColorName() << " " << warrior->getTypeName() << " " << warrior->getNumber()
                  << " born with strength " << warrior->getHP();

        // Print info about the current warrior's type and total count
        std::cout << "," << this->m_warriors_count[warrior_inedx] << " " << warrior->getTypeName()
                  << " in " << this->getColorName() << " headquarter"
                  << std::endl;

        // Print info about the current warrior's weapon & morale / loyalty
        logWarriorInfo(warrior);

        // 将 warrior 插入到 Headquarter 的容器中

        m_warriors.emplace_back(std::move(warrior));

    } else {

        std::cout << std::setw(3) << std::setfill('0') << m_totalWarriors << ' '
                  << this->getColorName()
                  << " headquarter stops making warriors"
                  << std::endl;
        return false;
    }

    return true;
}

void Headquarter::logWarriorInfo(std::unique_ptr<Warrior>& warrior)
{
    switch (warrior->getType()) {
    case WarriorType::dragon:
        warrior->setMorale(static_cast<double>(this->getLife()) / static_cast<double>(warrior->getHP()));
        std::cout << "It has a " << warrior->getWeapon(0)->getName() << ",and it's morale is " << std::fixed << std::setprecision(2) << warrior->getMorale() << std::endl;
        break;
    case WarriorType::ninja:
        std::cout << "It has a " << warrior->getWeapon(0)->getName() << " and a " << warrior->getWeapon(1)->getName() << std::endl;
        break;
    case WarriorType::iceman:
        std::cout << "It has a " << warrior->getWeapon(0)->getName() << std::endl;
        break;
    case WarriorType::lion:
        warrior->setLoyalty(this->getLife());
        std::cout << "It's loyalty is " << warrior->getLoyalty() << std::endl;
        break;
    case WarriorType::wolf:
        break;
    default:
        break;
    }
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
