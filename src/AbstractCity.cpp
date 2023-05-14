#include "../include/AbstractCity.h"
#include "../include/Warrior.h"
#include <iostream>
#include <memory>

// warrior add & remove
void AbstractCity::addWarrior(std::shared_ptr<Warrior> warrior, head_color color)
{
    // 判断是否已经存在对应颜色的武士
    if (hasWarrior(color)) {
        return;
    } else {
        if (color == head_color::red) {
            m_redWarriorExists = true;
            m_warriors_red.emplace_back(warrior);
        } else {
            m_blueWarriorExists = true;
            m_warriors_blue.emplace_back(warrior);
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
void AbstractCity::removeWarrior(std::shared_ptr<Warrior> warrior)
{
    if (warrior->getHeadColor() == head_color::red) {
        // 从 m_warriors_red 中移除
        if (!m_warriors_red.empty()) {
            m_warriors_red.pop_back();
        }

    } else {
        // 从 m_warriors_blue 中移除
        if (!m_warriors_blue.empty()) {
            m_warriors_blue.pop_back();
        }
    }
}

// battle
void AbstractCity::battle()
{
    if (m_redWarriorExists && m_blueWarriorExists) {
        // 塔塔开~
        while (this->m_warriors_red.back()->isAlive() || this->m_warriors_red.back()->isAlive()) {
            this->attackOnBattle(this->m_warriors_red[0], this->m_warriors_blue[0]);
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
        return m_warriors_blue[0];
    } else {
        return m_warriors_red[0];
    }
}