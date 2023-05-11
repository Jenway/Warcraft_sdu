// src\Headquarter.cpp 司令部类的实现

#include <algorithm>
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

void Headquarter::logWarriorInfo(std::unique_ptr<Warrior>& warrior)
{
    switch (warrior->getType()) {
    case WarriorType::dragon:
        warrior->setMorale(static_cast<double>(this->getLife()) / static_cast<double>(warrior->getHP()));
        std::cout << "It has a " << warrior->getWeapon(0)->getWeaponName() << ",and it's morale is " << std::fixed << std::setprecision(2) << warrior->getMorale() << std::endl;
        break;
    case WarriorType::ninja:
        std::cout << "It has a " << warrior->getWeapon(0)->getWeaponName() << " and a " << warrior->getWeapon(1)->getWeaponName() << std::endl;
        break;
    case WarriorType::iceman:
        std::cout << "It has a " << warrior->getWeapon(0)->getWeaponName() << std::endl;
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

void Headquarter::warriorsMarch()
{
    for (auto& warrior : m_warriors) {
        warrior->march();
    }
}

void Headquarter::wolfSnatch()
{
    for (auto& warrior : m_warriors) {
        if (warrior->getType() == WarriorType::wolf) {
            std::shared_ptr<Wolf> wolf = std::dynamic_pointer_cast<Wolf>(warrior);
            // TODO wolf snatch
        }
    }
}

void Headquarter::reportBattle()
{
    for (auto& warrior : m_warriors) {
        std::cout << " " << warrior->getHP() << " " << warrior->getTypeName() << " in " << this->getColorName() << " headquarter" << std::endl;
    }
}

void Headquarter::warriorYell()
{
    for (auto& warrior : m_warriors) {
        if (warrior->getType() == WarriorType::dragon) {
            std::shared_ptr<Dragon> dragon = std::dynamic_pointer_cast<Dragon>(warrior);
            dragon->yell();
        }
    }
}

void Headquarter::reportLife()
{
    // TODO 每小时第 50 分,司令部报告生命值
    // 000:50 120 elements in blue headquarter
    std::cout << "000:50 120 elements in blue headquarter";
}

// 事件处理函数接口

bool Headquarter::createWarrior()
{
    int hour = this->clock->getHours();
    int minute = this->clock->getMinutes();
    const auto& warrior_order = (Headquarter::getColor() == head_color::red) ? warrior_order_red : warrior_order_blue;

    auto index = warrior_order[m_warrior_index];

    // 判断是否能够创建 warrior

    while (!isAbleToCreate(static_cast<int>(index))) {
        this->m_warrior_index = (this->m_warrior_index + 1) % 5;
        index = warrior_order[m_warrior_index];
    }

    if (isAbleToCreate(static_cast<int>(index))) {
        auto warrior = WarriorFactory::createWarrior(index, m_totalWarriors + 1, this->getColor()); // index starts from 1, not 0. (index 0 is the hero;

        int warrior_inedx = static_cast<int>(warrior->getType());

        // 对Headquarter的成员变量进行修改
        this->m_totalWarriors++;
        this->m_warrior_index = (this->m_warrior_index + 1) % 5;
        this->m_warriors_count[warrior_inedx]++;
        this->setLifeViaCost(warrior->getHP());
        // fix it later

        // log (part 3)
        std::cout << std::setw(3) << std::setfill('0') << hour << ':' << std::setw(2) << std::setfill('0') << minute << ' '
                  << this->getColorName() << " " << warrior->getTypeName() << " " << warrior->getNumber()
                  << " born" << std::endl;
        if (warrior->getType() == WarriorType::lion) {
            std::cout << "Its loyalty is " << warrior->getLoyalty() << std::endl;
        }
#if defined(HISTORY_FILE)
// below is log info of part 1&2
// // 输出 log 信息
// // Print info about the current warrior
// std::cout << std::setw(3) << std::setfill('0') << m_totalWarriors - 1 << ' '
//           << this->getColorName() << " " << warrior->getTypeName() << " " << warrior->getNumber()
//           << " born with strength " << warrior->getHP();

// // Print info about the current warrior's type and total count
// std::cout << "," << this->m_warriors_count[warrior_inedx] << " " << warrior->getTypeName()
//           << " in " << this->getColorName() << " headquarter"
//           << std::endl;

// // Print info about the current warrior's weapon & morale / loyalty
// logWarriorInfo(warrior);
#endif
        // 将 Headquarter 的弱指针指向 warrior
        warrior->setHomeWeakPtr(std::make_shared<Headquarter>(*this));
        // 将 warrior 插入到 Headquarter 的容器中
        m_warriors.emplace_back(std::move(warrior));

    } else {
#if defined(HISTORY_FILE)
        // std::cout << std::setw(3) << std::setfill('0') << m_totalWarriors << ' '
        //           << this->getColorName()
        //           << " headquarter stops making warriors"
        //           << std::endl;
        // 设置 headquarter 的状态为停止创建 warrior
#endif
        this->stopCreate();
        return false;
    }

    return true;
}

void Headquarter::lionEscape()
{
    int hour = this->clock->getHours();
    int minute = this->clock->getMinutes();
    // 遍历容器中的lion
    for (auto& warrior : m_warriors) {
        if (warrior->getType() == WarriorType::lion) {
            // 如果lion的忠诚度小于等于0，则lion逃跑
            if (warrior->getLoyalty() <= 0) {
                // e.g. 000:05 blue lion 1 ran away
                std::cout << std::setw(3) << std::setfill('0') << hour << ':' << std::setw(2) << std::setfill('0') << minute << ' '
                          << this->getColorName() << " " << warrior->getTypeName() << " " << warrior->getNumber()
                          << " ran away" << std::endl;
                // 从容器中移除lion
                // 保留lion的指针，调用lion的析构函数与lion的指针置空
                std::shared_ptr<Lion> lion = std::dynamic_pointer_cast<Lion>(warrior);
                // 析构函数会自动把lion在city和headquarter中的指针置空
                lion->escape();
                removeWarrior(warrior);
                lion.reset();
            }
        }
    }
}

void Headquarter::warriorsMarch()
{
    for (auto& warrior : m_warriors) {
        warrior->march();
    }
}

void Headquarter::wolfSnatch()
{
    for (auto& warrior : m_warriors) {
        if (warrior->getType() == WarriorType::wolf) {
            std::shared_ptr<Wolf> wolf = std::dynamic_pointer_cast<Wolf>(warrior);
            // TODO wolf snatch
        }
    }
}

void Headquarter::reportBattle()
{
    for (auto& warrior : m_warriors) {
        std::cout << " " << warrior->getHP() << " " << warrior->getTypeName() << " in " << this->getColorName() << " headquarter" << std::endl;
    }
}

void Headquarter::warriorYell()
{
    for (auto& warrior : m_warriors) {
        if (warrior->getType() == WarriorType::dragon) {
            std::shared_ptr<Dragon> dragon = std::dynamic_pointer_cast<Dragon>(warrior);
            dragon->yell();
        }
    }
}

void Headquarter::reportLife()
{
    // TODO 每小时第 50 分,司令部报告生命值
    // 000:50 120 elements in blue headquarter
    std::cout << "000:50 120 elements in blue headquarter";
}

void Headquarter::reportWeapon(int hour, int minute)
{
    for (auto& warrior : m_warriors) {
        warrior->reportWeapon(hour, minute);
    }
}