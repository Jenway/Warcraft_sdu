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
    int hour = this->clock->getHours(), minute = this->clock->getMinutes();
    // 获取生成顺序，本次生成的战士类型
    const auto& warrior_order = (Headquarter::getColor() == head_color::red) ? warrior_order_red : warrior_order_blue;
    auto index = warrior_order[m_warrior_index];
    // 判断是否能够创建 warrior
    if (!isAbleToCreate(static_cast<int>(index))) {
        return false;
    }

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
    if (warrior->getType() == WarriorType::lion) {

        warrior->setLoyalty(this->getLife());
        std::cout << "Its loyalty is " << warrior->getLoyalty() << std::endl;
    }
    // set city and home pointer
    warrior->setCity(shared_from_this());
    warrior->setHomePtr(std::dynamic_pointer_cast<Headquarter>(shared_from_this()));
    // 将 warrior 插入到 Headquarter 的容器中
    m_warriors.emplace_back(warrior);
    // 将 warrior 插入到 Headquarter 的作为城市的容器中
    this->addWarrior(warrior, warrior->getHeadColor());
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

void Headquarter::reportLife()
{
    int hour = this->clock->getHours();
    int minute = this->clock->getMinutes();
    // 001:50 20 elements in red headquarter
    std::cout << std::setw(3) << std::setfill('0') << hour << ':' << std::setw(2) << std::setfill('0') << minute << ' ' << this->getLife() << " elements in " << this->getColorName() << " headquarter" << std::endl;
}

bool Headquarter::isAbleToCreate(int warrior_index)
{
    return (this->m_life >= Warrior::getLifeCost(warrior_index));
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
    // TODO 析构函数实现
}