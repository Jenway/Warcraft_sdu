// src\Headquarter.cpp 司令部类的实现

#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>

#include "../include/Headquarter.h"
#include "../include/Warrior.h"
#include "../include/WarriorFactory.h"

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

// 事件处理函数接口

bool Headquarter::createWarrior()
{
    // 获取时间
    int hour = this->clock->getHours();
    int minute = this->clock->getMinutes();
    // 获取生成顺序，本次生成的战士类型
    const auto& warrior_order = (Headquarter::getColor() == head_color::red) ? warrior_order_red : warrior_order_blue;
    auto index = warrior_order[m_warrior_index];
    // 判断是否能够创建 warrior
    // int rangeCount = 0;
    if (!isAbleToCreate(static_cast<int>(index))) {
        return false;
    }
    /*
    //原来在 part2中的设定: 如果不能创建，就跳过这个 warrior，继续下一个
    while (!isAbleToCreate(static_cast<int>(index))) {
        this->m_warrior_index = (this->m_warrior_index + 1) % 5;
        index = warrior_order[m_warrior_index];
        // 这里应该有一个判断，如果所有的 warrior 都不能创建了，就返回 false
        // 但是每次开始的 indice 都不同，所以要从循环的次数来判断
        if (++rangeCount > 5) {
            this->stopCreate();
            return false;
        }
    }
    */

    // 调用 WarriorFactory 创建 warrior 传入 类型、编号和颜色
    auto warrior = WarriorFactory::createWarrior(index, m_totalWarriors + 1, this->getColor()); // index starts from 1, not 0. (index 0 is the hero;

    int warrior_inedx = static_cast<int>(warrior->getType());
    // 对Headquarter的成员变量进行修改
    this->m_totalWarriors++;
    // 这里本来打算用个 map 来存储 每种warrior各自 的数量，但是感觉没必要，直接用数组就行了
    this->m_warriors_count[warrior_inedx]++;
    this->m_warrior_index = (this->m_warrior_index + 1) % 5;
    this->setLifeViaCost(warrior->getHP());
    // log (part 3)
    std::cout << std::setw(3) << std::setfill('0') << hour << ':' << std::setw(2) << std::setfill('0') << minute << ' '
              << this->getColorName() << " " << warrior->getTypeName() << " " << warrior->getNumber()
              << " born" << std::endl;
    if (warrior->getType() == WarriorType::dragon) {
        warrior->setMorale(static_cast<double>(this->getLife()) / static_cast<double>(warrior->getHP()));
        std::cout << "Its morale is " << std::fixed << std::setprecision(2) << warrior->getMorale() << std::endl;
    }
    if (warrior->getType() == WarriorType::lion) {

        warrior->setLoyalty(this->getLife());
        std::cout << "Its loyalty is " << warrior->getLoyalty() << std::endl;
    }
    warrior->setCity(shared_from_this());
    
    m_warriors.emplace_back(warrior);
    // 将 warrior 插入到 Headquarter 的作为城市的容器中
    this->addWarrior(warrior, warrior->getHeadColor());
    // 将 warrior 插入到 Headquarter 的容器中
    // TODO 怎么在战士死亡后删除呢？

    return true;
}

// 下一个城市

std::shared_ptr<AbstractCity> Headquarter::nextCity(head_color warrior_color)
{
    if (warrior_color == head_color::red) {
        return this->m_rightCity;
    } else {
        return this->m_leftCity;
    }
}

void Headquarter::lionEscape()
{
    int hour = this->clock->getHours();
    int minute = this->clock->getMinutes();
    // 遍历容器中的lion

    for (auto i = m_warriors.begin(); i != m_warriors.end();) {
        auto warrior = *i;
        if (warrior->getType() == WarriorType::lion) {
            // 如果lion的忠诚度小于等于0，则lion逃跑
            if (warrior->getLoyalty() <= 0) {
                // std::cout << "the loyalty of " << warrior->getTypeName() << " " << warrior->getNumber() << " is 0" << std::endl;
                // e.g. 000:05 blue lion 1 ran away
                std::cout << std::setw(3) << std::setfill('0') << hour << ':' << std::setw(2) << std::setfill('0') << minute << ' '
                          << this->getColorName() << " " << warrior->getTypeName() << " " << warrior->getNumber()
                          << " ran away" << std::endl;
                // 从容器中移除lion
                // 保留lion的指针，调用lion的析构函数与lion的指针置空
                std::shared_ptr<Lion> lion = std::dynamic_pointer_cast<Lion>(warrior);
                // 析构函数会自动把lion在city和headquarter中的指针置空
                lion->escape();
                // 判断lion是否在city中，如果在，则从city中移除lion
                lion.reset();
                // 删除在headquarter中的lion的指针
                i = m_warriors.erase(i);
            } else {
                ++i;
            }
        } else {
            ++i;
        }
    }
}

void Headquarter::wolfSnatch()
{
    for (auto& warrior : m_warriors) {
        if (warrior->getType() == WarriorType::wolf) {
            std::shared_ptr<Wolf> wolf = std::dynamic_pointer_cast<Wolf>(warrior);
            // TODO wolf snatch
            // wolf->robWeapon();
        }
    }
}

void Headquarter::reportLife()
{
    // TODO 每小时第 50 分,司令部报告生命值
    // 000:50 120 elements in blue headquarter

    int hour = this->clock->getHours();
    int minute = this->clock->getMinutes();
    // 001:50 20 elements in red headquarter
    std::cout << std::setw(3) << std::setfill('0') << hour << ':' << std::setw(2) << std::setfill('0') << minute << ' ' << this->getLife() << " elements in " << this->getColorName() << " headquarter" << std::endl;
}
void Headquarter::reportBattle()
{
    // TODO
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

bool Headquarter::isAbleToCreate(int warrior_index)
{
    if (this->m_life < Warrior::getLifeCost(warrior_index)) {
        return false;
    }
    return true;
}

Headquarter::Headquarter(int life, head_color color)
{
    // 构造函数实现
    this->m_color = color;
    this->m_life = life;
    this->m_totalWarriors = 0;
    this->isThisHeadquater = true;
}

Headquarter::~Headquarter()
{
    // 析构函数实现
    // 析构函数会自动把lion在city和headquarter中的指针置空
    for (auto& warrior : m_warriors) {
        // warrior->escape();
        warrior->~Warrior();
    }
    m_warriors.clear();
}