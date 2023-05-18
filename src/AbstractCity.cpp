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
                if (this->isHeadquarter()) {
                    std::cout << warrior->getHeadColorName() << ' ' << warrior->getTypeName() << ' ' << warrior->getNumber() << " reached " << this->getHeadColorName() << " headquarter"
                              << " with " << warrior->getHP() << " elements and force " << warrior->getAttack() << std::endl;

                    if (this->isOccupied()) {
                        std::cout << std::setw(3) << std::setfill('0') << hour << ':' << std::setw(2) << std::setfill('0') << minute << ' ';
                        std::cout << this->getHeadColorName() << " headquarter was taken" << std::endl;
                    }
                } else {
                    std::cout << warrior->getHeadColorName() << ' ' << warrior->getTypeName() << ' ' << warrior->getNumber() << " marched to city " << this->getCityNumber() << " with " << warrior->getHP() << " elements and force " << warrior->getAttack() << std::endl;
                }
            }
        }
    }
    if (m_blueWarriorExists) {
        for (auto i = 0; i < m_warriors_blue.size(); i++) {
            auto warrior = m_warriors_blue[i];
            if (warrior->isJustArrived()) {
                // 000:10 red iceman 1 marched to city 1 with 20 elements and force 30
                std::cout << std::setw(3) << std::setfill('0') << hour << ':' << std::setw(2) << std::setfill('0') << minute << ' ';
                if (this->isHeadquarter()) {
                    std::cout << warrior->getHeadColorName() << ' ' << warrior->getTypeName() << ' ' << warrior->getNumber() << " reached " << this->getHeadColorName() << " headquarter"
                              << " with " << warrior->getHP() << " elements and force " << warrior->getAttack() << std::endl;
                    
                    if (this->isOccupied()) {
                        std::cout << std::setw(3) << std::setfill('0') << hour << ':' << std::setw(2) << std::setfill('0') << minute << ' ';
                        std::cout << this->getHeadColorName() << " headquarter was taken" << std::endl;
                    }
                } else {
                    std::cout << warrior->getHeadColorName() << ' ' << warrior->getTypeName() << ' ' << warrior->getNumber() << " marched to city " << this->getCityNumber() << " with " << warrior->getHP() << " elements and force " << warrior->getAttack() << std::endl;
                }
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
        bool onBattle = true;
        auto red = m_warriors_red.back();
        auto blue = m_warriors_blue.back();
        red->sortWeapon();
        blue->sortWeapon();
        while (onBattle) {
            this->attackOnBattle(red, blue);

            // 战斗结束判断
            // 1. 有战士死亡
            if (!red->isAlive() || !blue->isAlive()) {
                onBattle = false;
            }
            // 2. 两者都没有武器
            if (red->getWeapons().empty() && blue->getWeapons().empty()) {
                onBattle = false;
            }
        }
        this->isJustBattled = true;
    }
}

// report life

// report battle

void AbstractCity::reportBattle(int hour, int minute)
{
    if (this->isJustBattled) {

        auto warrior_red = m_warriors_red.back();
        auto warrior_blue = m_warriors_blue.back();
        std::cout << std::setw(3) << std::setfill('0') << hour << ':' << std::setw(2) << std::setfill('0') << minute << ' ';
        if (warrior_red->isAlive() && warrior_blue->isAlive()) {

            std::cout << "both " << warrior_red->getHeadColorName() << ' ' << warrior_red->getTypeName() << ' ' << warrior_red->getNumber() << " and " << warrior_blue->getHeadColorName() << ' ' << warrior_blue->getTypeName() << ' ' << warrior_blue->getNumber() << " were alive in city " << this->getCityNumber() << std::endl;
        } else if (warrior_red->isAlive() && !warrior_blue->isAlive()) {
            std::cout << warrior_red->getHeadColorName() << ' ' << warrior_red->getTypeName() << ' ' << warrior_red->getNumber() << " killed " << warrior_blue->getHeadColorName() << ' ' << warrior_blue->getTypeName() << ' ' << warrior_blue->getNumber() << " in city " << this->getCityNumber() << " remaining " << warrior_red->getHP() << " elements" << std::endl;
        } else if (warrior_blue->isAlive() && !warrior_red->isAlive()) {
            std::cout << warrior_blue->getHeadColorName() << ' ' << warrior_blue->getTypeName() << ' ' << warrior_blue->getNumber() << " killed " << warrior_red->getHeadColorName() << ' ' << warrior_red->getTypeName() << ' ' << warrior_red->getNumber() << " in city " << this->getCityNumber() << " remaining " << warrior_blue->getHP() << " elements" << std::endl;
        } else {
            std::cout << "both " << warrior_red->getHeadColorName() << ' ' << warrior_red->getTypeName() << ' ' << warrior_red->getNumber() << " and " << warrior_blue->getHeadColorName() << ' ' << warrior_blue->getTypeName() << ' ' << warrior_blue->getNumber() << " died in city " << this->getCityNumber() << std::endl;
        }
        // 战士派生类的报告
        if (warrior_red->getType() == WarriorType::dragon && warrior_red->isAlive()) {

            // 003:40 blue dragon 2 yelled in city 4
            std::cout << std::setw(3) << std::setfill('0') << hour << ':' << std::setw(2) << std::setfill('0') << minute << ' ';
            std::cout << warrior_red->getHeadColorName() << ' ' << warrior_red->getTypeName() << ' ' << warrior_red->getNumber() << " yelled in city " << this->getCityNumber() << std::endl;
        }

        if (warrior_blue->getType() == WarriorType::dragon && warrior_blue->isAlive()) {
            std::cout << std::setw(3) << std::setfill('0') << hour << ':' << std::setw(2) << std::setfill('0') << minute << ' ';
            std::cout << warrior_blue->getHeadColorName() << ' ' << warrior_blue->getTypeName() << ' ' << warrior_blue->getNumber() << " yelled in city " << this->getCityNumber() << std::endl;
        }
    }
}

void AbstractCity::attackOnBattle(std::shared_ptr<Warrior> red, std::shared_ptr<Warrior> blue)
{
    // attack
    // 奇数编号城市，红方先攻击
    if (this->getCityNumber() % 2 == 1) {
        if (red->isAlive()) {
            red->attack(blue);
        }
        if (blue->isAlive()) {

            blue->attack(red);
        }
    } else {
        if (blue->isAlive()) {
            blue->attack(red);
        }
        if (red->isAlive()) {
            red->attack(blue);
        }
    }
}

void AbstractCity::afterBattle()
{
    if (this->isJustBattled) {

        // 战斗结束，重置标志位
        this->isJustBattled = false;
        // TODO 判断是否有战士死亡 并设置死亡
        auto red = m_warriors_red.back();
        auto blue = m_warriors_blue.back();
        // 获取武器
        // 两者都存活 则 pass
        if (red->isAlive() && blue->isAlive()) {
            return;
        }
        // 一方死亡，另一方存活
        if (red->isAlive() && !blue->isAlive()) {
            red->pickWeapons(blue);
        }
        if (blue->isAlive() && !red->isAlive()) {
            blue->pickWeapons(blue);
        }
        // 清理内存
        if (!red->isAlive()) {
            // 取出武器
            auto weapons = red->dropWeapons();
            this->weapons.insert(this->weapons.end(), weapons.begin(), weapons.end());
            red->die();
            this->m_redWarriorExists = false;
            m_warriors_red.clear();
            // std::cout << "red die" << m_warriors_red.size() << std::endl;
        }
        if (!blue->isAlive()) {
            // 取出武器
            auto weapons = blue->dropWeapons();
            this->weapons.insert(this->weapons.end(), weapons.begin(), weapons.end());
            blue->die();
            this->m_blueWarriorExists = false;
            m_warriors_blue.clear();
            // std::cout << "blue die" << m_warriors_blue.size() << std::endl;
        }
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

void AbstractCity::wolfSnatch(int hour, int minute)
{
    if (m_redWarriorExists && m_blueWarriorExists) {
        auto red = m_warriors_red.back();
        auto blue = m_warriors_blue.back();
        if (red->getType() == WarriorType::wolf && blue->getType() != WarriorType::wolf) {
            dynamic_cast<Wolf*>(red.get())->snatchWeapons(blue, hour, minute);
        }
        if (blue->getType() == WarriorType::wolf && red->getType() != WarriorType::wolf) {
            // 蓝方是狼，红方不是狼
            dynamic_cast<Wolf*>(blue.get())->snatchWeapons(red, hour, minute);
        }
    }
}