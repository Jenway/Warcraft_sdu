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
    if (hasWarrior(color)) {
        return;
    } else {
        if (color == head_color::red) {
            m_redWarriorExists = true;
            m_warriors_red = warrior;
        } else {
            m_blueWarriorExists = true;
            m_warriors_blue = warrior;
        }
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

// 这个函数仅会删除 city 中的 warrior 指针
void AbstractCity::removeWarrior(head_color color)
{
    if (color == head_color::red) {
        m_warriors_red.reset();
        m_redWarriorExists = false;

    } else {
        m_warriors_blue.reset();
        m_blueWarriorExists = false;
    }
}

void AbstractCity::reportWeapon(int hour, int minute)
{
    if (m_redWarriorExists) {
        std::cout << std::setfill('0') << std::setw(3) << hour << ":" << std::setw(2) << minute << " ";
        std::cout << "red " << m_warriors_red->getTypeName() << " " << m_warriors_red->getNumber() << " has ";
        m_warriors_red->reportWeapon(hour, minute);
    }
    if (m_blueWarriorExists) {
        std::cout << std::setfill('0') << std::setw(3) << hour << ":" << std::setw(2) << minute << " ";
        std::cout << "blue " << m_warriors_blue->getTypeName() << " " << m_warriors_blue->getNumber() << " has ";
        m_warriors_blue->reportWeapon(hour, minute);
    }
}

// battle
void AbstractCity::battle()
{
    if (m_redWarriorExists && m_blueWarriorExists) {
        // 塔塔开~
        while (this->m_warriors_red->isAlive() || this->m_warriors_red->isAlive()) {
            this->attackOnBattle(this->m_warriors_red, this->m_warriors_blue);
        }
    } else {
        return;
    }
}

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
        return m_warriors_blue;
    } else {
        return m_warriors_red;
    }
}