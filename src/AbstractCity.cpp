#include "../include/AbstractCity.h"
#include "../include/Warrior.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// warrior add & remove
void AbstractCity::addWarrior(std::shared_ptr<Warrior> warrior, head_color color)
{
    // 判断是否已经存在对应颜色的武士

    if (color == head_color::red) {
        m_redWarriorExists = true;
        m_warriors_red.emplace_back(warrior);
    } else {
        m_blueWarriorExists = true;
        m_warriors_blue.emplace_back(warrior);
    }
}

bool AbstractCity::hasWarrior(head_color color)
{
    if (color == head_color::red) {
        return m_redWarriorExists;
    } else {
        return m_blueWarriorExists;
    }
}

// warrior march

void AbstractCity::warriorMarch()
{

    if (m_redWarriorExists) {
        // std::shared_ptr<AbstractCity> nextCity = this->nextCity(head_color::red);
        // 为什么这里不用 for (auto warrior : m_warriors_red) ?
        // 因为循环中会删除m_warriors_red 中的元素，会导致迭代器失效
        for (auto i = 0; i < m_warriors_red.size(); i++) {
            auto warrior = m_warriors_red[i];
            if (!warrior->isJustArrived()) {
                warrior->setJustArrived(true);
                warrior->march();
            }
        }
    }

    if (m_blueWarriorExists) {
        for (auto i = 0; i < m_warriors_blue.size(); i++) {
            auto warrior = m_warriors_blue[i];
            if (!warrior->isJustArrived()) {
                warrior->setJustArrived(true);
                warrior->march();
            }
        }
    }
}

// report warriors march

void AbstractCity::reportWarriorMarch(int hour, int minute)
{
    if (m_redWarriorExists) {
        for (auto i = 0; i < m_warriors_red.size(); i++) {
            auto warrior = m_warriors_red[i];
            if (warrior->isJustArrived()) {
                // 000:10 red iceman 1 marched to city 1 with 20 elements and force 30
                std::cout << std::setw(3) << std::setfill('0') << hour << ':' << std::setw(2) << std::setfill('0') << minute << ' ';
                std::cout << warrior->getHeadColorName() << ' ' << warrior->getTypeName() << ' ' << warrior->getNumber() << " marched to city " << this->getCityNumber() + 1 << " with " << warrior->getHP() << " elements and force " << warrior->getAttack() << std::endl;
            }
        }
    }
    if (m_blueWarriorExists) {
        for (auto i = 0; i < m_warriors_blue.size(); i++) {
            auto warrior = m_warriors_blue[i];
            if (warrior->isJustArrived()) {
                // 000:10 red iceman 1 marched to city 1 with 20 elements and force 30
                std::cout << std::setw(3) << std::setfill('0') << hour << ':' << std::setw(2) << std::setfill('0') << minute << ' ';
                std::cout << warrior->getHeadColorName() << ' ' << warrior->getTypeName() << ' ' << warrior->getNumber() << " marched to city " << this->getCityNumber() + 1 << " with " << warrior->getHP() << " elements and force " << warrior->getAttack() << std::endl;
            }
        }
    }
}

// 这个函数仅会删除 city 中的 warrior 指针
void AbstractCity::removeWarrior(head_color color, std::shared_ptr<Warrior> warrior)
{
    if (color == head_color::red) {
        m_warriors_red.erase(std::remove(m_warriors_red.begin(), m_warriors_red.end(), warrior), m_warriors_red.end());
        if (m_warriors_red.empty()) {
            m_redWarriorExists = false;
        }
    } else {
        m_warriors_blue.erase(std::remove(m_warriors_blue.begin(), m_warriors_blue.end(), warrior), m_warriors_blue.end());
        if (m_warriors_blue.empty()) {
            m_blueWarriorExists = false;
        }
    }
}

void AbstractCity::reportWeapon(int hour, int minute)
{
    if (m_redWarriorExists) {
        m_warriors_red.back()->reportWeapon(hour, minute);
    }
    if (m_blueWarriorExists) {
        m_warriors_blue.back()->reportWeapon(hour, minute);
    }
}

// battle
void AbstractCity::battle()
{
    if (m_redWarriorExists && m_blueWarriorExists) {
        // 塔塔开~
        while (this->m_warriors_red.back()->isAlive() || this->m_warriors_red.back()->isAlive()) {
            this->attackOnBattle(this->m_warriors_red.back(), this->m_warriors_blue.back());
        }
    } else {
        return;
    }
}

// report life

void AbstractCity::attackOnBattle(std::shared_ptr<Warrior> red, std::shared_ptr<Warrior> blue)
{
    // wolf 抢武器
    if (red->getType() == WarriorType::wolf) {

        // warrior_on_attack->robWeapon();
        auto robbing_wolf = std::make_shared<Wolf>(blue);
        robbing_wolf->robWeapon();
    }
    if (blue->getType() == WarriorType::wolf) {
        auto robbing_wolf = std::make_shared<Wolf>(red);
        robbing_wolf->robWeapon();
    }
    // attack
    red->attack(blue);
    if (blue->isAlive()) {
        blue->attack(red);
    }
    // 死亡判断
    if (!red->isAlive()) {
        for (auto& weapon : red->getWeapons()) {
            this->weapons.push_back(weapon);
        }
        red->die();
    }
    if (!blue->isAlive()) {
        for (auto& weapon : blue->getWeapons()) {
            this->weapons.push_back(weapon);
        }
        blue->die();
    }
    // 获取武器
    if (red->isAlive()) {
        red->getWeapon(this->weapons);
    }
    // 为战士欢呼设定状态
    if (red->isAlive() && !blue->isAlive() && red->getType() == WarriorType::dragon) {
        std::shared_ptr<Dragon> red_dragon = std::dynamic_pointer_cast<Dragon>(red);
        red_dragon->setCheerStatus();
    }

    if (!red->isAlive() && blue->isAlive() && blue->getType() == WarriorType::dragon) {
        std::shared_ptr<Dragon> blue_dragon = std::dynamic_pointer_cast<Dragon>(blue);
        blue_dragon->setCheerStatus();
    }
}

std::shared_ptr<Warrior> AbstractCity::getEnemy(head_color color)
{
    if (color == head_color::red) {
        return m_warriors_blue.back();
    } else {
        return m_warriors_red.back();
    }
}