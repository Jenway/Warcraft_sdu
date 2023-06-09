#include "../include/AbstractCity.h"
#include "../include/GameIO.h"
#include "../include/Warrior.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
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

// warrior march

void AbstractCity::warriorMarch()
{
    if (m_redWarriorExists) {
        warriorMarchForColor(m_warriors_red);
    }

    if (m_blueWarriorExists) {
        warriorMarchForColor(m_warriors_blue);
    }
}
void AbstractCity::warriorMarchForColor(std::vector<std::shared_ptr<Warrior>>& warriors)
{
    // 为什么这里不用 for (auto warrior : m_warriors_red) ?
    // 因为循环中会删除warriors 中的元素，会导致迭代器失效
    for (auto i = 0; i < warriors.size(); i++) {
        auto& warrior = warriors[i];
        if (!warrior->isJustArrived()) {
            warrior->setJustArrived(true);
            warrior->march();
        }
    }
}
// report warriors march
void AbstractCity::reportWarriorMarch(int hour, int minute)
{
    if (m_redWarriorExists) {
        reportWarriorMarchForColor(m_warriors_red, hour, minute);
    }
    if (m_blueWarriorExists) {
        reportWarriorMarchForColor(m_warriors_blue, hour, minute);
    }
}

void AbstractCity::reportWarriorMarchForColor(std::vector<std::shared_ptr<Warrior>>& warriors, int& hour, int& minute)
{
    std::stringstream ss;
    for (auto i = 0; i < warriors.size(); i++) {
        auto& warrior = warriors[i];
        if (warrior->isJustArrived()) {
            // 000:10 red iceman 1 marched to city 1 with 20 elements and force 30
            ss << std::setw(3) << std::setfill('0') << hour << ':' << std::setw(2) << std::setfill('0') << minute << ' ';
            std::string str = ss.str();
            if (this->isHeadquarter()) {
                ss << warrior->getHeadColorName() << ' ' << warrior->getTypeName() << ' ' << warrior->getNumber() << " reached " << this->getHeadColorName() << " headquarter"
                   << " with " << warrior->getHP() << " elements and force " << warrior->getAttack() << std::endl;
                gameIO::print(ss.str());
                if (this->isOccupied()) {
                    std::stringstream ss2;
                    ss2 << std::setw(3) << std::setfill('0') << hour << ':' << std::setw(2) << std::setfill('0') << minute << ' ';
                    ss2 << this->getHeadColorName() << " headquarter was taken" << std::endl;
                    gameIO::print(ss2.str());
                }
            } else {
                ss << warrior->getHeadColorName() << ' ' << warrior->getTypeName() << ' ' << warrior->getNumber() << " marched to city " << this->getCityNumber() << " with " << warrior->getHP() << " elements and force " << warrior->getAttack() << std::endl;
                gameIO::print(ss.str());
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
        auto& red = m_warriors_red.back();
        auto& blue = m_warriors_blue.back();
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
            // 3. 生命值和武器状态都没有变化
            if (red->unchanged() && blue->unchanged()) {
                onBattle = false;
            }
        }
        this->isJustBattled = true;
    }
}

// report battle

void AbstractCity::reportBattle(int hour, int minute)
{

    if (this->isJustBattled) {
        std::stringstream ss;
        auto& warrior_red = m_warriors_red.back();
        auto& warrior_blue = m_warriors_blue.back();
        ss << std::setw(3) << std::setfill('0') << hour << ':' << std::setw(2) << std::setfill('0') << minute << ' ';
        if (warrior_red->isAlive() && warrior_blue->isAlive()) {

            ss << "both " << warrior_red->getHeadColorName() << ' ' << warrior_red->getTypeName() << ' ' << warrior_red->getNumber() << " and " << warrior_blue->getHeadColorName() << ' ' << warrior_blue->getTypeName() << ' ' << warrior_blue->getNumber() << " were alive in city " << this->getCityNumber() << std::endl;
            gameIO::print(ss.str());
        } else if (warrior_red->isAlive() && !warrior_blue->isAlive()) {
            ss << warrior_red->getHeadColorName() << ' ' << warrior_red->getTypeName() << ' ' << warrior_red->getNumber() << " killed " << warrior_blue->getHeadColorName() << ' ' << warrior_blue->getTypeName() << ' ' << warrior_blue->getNumber() << " in city " << this->getCityNumber() << " remaining " << warrior_red->getHP() << " elements" << std::endl;
            gameIO::print(ss.str());
        } else if (warrior_blue->isAlive() && !warrior_red->isAlive()) {
            ss << warrior_blue->getHeadColorName() << ' ' << warrior_blue->getTypeName() << ' ' << warrior_blue->getNumber() << " killed " << warrior_red->getHeadColorName() << ' ' << warrior_red->getTypeName() << ' ' << warrior_red->getNumber() << " in city " << this->getCityNumber() << " remaining " << warrior_blue->getHP() << " elements" << std::endl;
            gameIO::print(ss.str());
        } else {
            ss << "both " << warrior_red->getHeadColorName() << ' ' << warrior_red->getTypeName() << ' ' << warrior_red->getNumber() << " and " << warrior_blue->getHeadColorName() << ' ' << warrior_blue->getTypeName() << ' ' << warrior_blue->getNumber() << " died in city " << this->getCityNumber() << std::endl;
            gameIO::print(ss.str());
        }
        // 战士派生类的报告
        if (warrior_red->getType() == WarriorType::dragon && warrior_red->isAlive()) {

            // 003:40 blue dragon 2 yelled in city 4
            std::stringstream ss2;
            ss2 << std::setw(3) << std::setfill('0') << hour << ':' << std::setw(2) << std::setfill('0') << minute << ' ';
            ss2 << warrior_red->getHeadColorName() << ' ' << warrior_red->getTypeName() << ' ' << warrior_red->getNumber() << " yelled in city " << this->getCityNumber() << std::endl;
            gameIO::print(ss2.str());
        }

        if (warrior_blue->getType() == WarriorType::dragon && warrior_blue->isAlive()) {
            std::stringstream ss2;
            ss2 << std::setw(3) << std::setfill('0') << hour << ':' << std::setw(2) << std::setfill('0') << minute << ' ';
            ss2 << warrior_blue->getHeadColorName() << ' ' << warrior_blue->getTypeName() << ' ' << warrior_blue->getNumber() << " yelled in city " << this->getCityNumber() << std::endl;
            gameIO::print(ss2.str());
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
        auto& red = m_warriors_red.back();
        auto& blue = m_warriors_blue.back();
        // 获取武器
        // 两者都存活 则 pass
        if (red->isAlive() && blue->isAlive()) {
            return;
        }
        // 一方死亡，另一方存活
        if (red->isAlive() && !blue->isAlive()) {
            red->pickWeapons(blue);
            this->m_blueWarriorExists = false;
            this->m_warriors_blue.pop_back();
        }
        if (blue->isAlive() && !red->isAlive()) {
            blue->pickWeapons(red);
            this->m_redWarriorExists = false;
            this->m_warriors_red.pop_back();
        }
    }
}

void AbstractCity::wolfSnatch(int hour, int minute)
{
    if (m_redWarriorExists && m_blueWarriorExists) {
        auto& red = m_warriors_red.back();
        auto& blue = m_warriors_blue.back();
        if (red->getType() == WarriorType::wolf && blue->getType() != WarriorType::wolf) {
            dynamic_cast<Wolf*>(red.get())->snatchWeapons(blue, hour, minute);
        }
        if (blue->getType() == WarriorType::wolf && red->getType() != WarriorType::wolf) {
            // 蓝方是狼，红方不是狼
            dynamic_cast<Wolf*>(blue.get())->snatchWeapons(red, hour, minute);
        }
    }
}

void AbstractCity::lionEscape(int hour, int minute)
{
    std::stringstream ss;
    if (m_redWarriorExists) {
        auto& red = m_warriors_red.back();
        if (red->getLoyalty() <= 0 && red->getType() == WarriorType::lion) {
            // std::cout << "the loyalty of " << warrior->getTypeName() << " " << warrior->getNumber() << " is 0" << std::endl;
            // e.g. 000:05 blue lion 1 ran away

            ss << std::setw(3) << std::setfill('0') << hour << ':' << std::setw(2) << std::setfill('0') << minute << ' '
               << red->getHeadColorName() << " " << red->getTypeName() << " " << red->getNumber()
               << " ran away" << std::endl;
            std::string str = ss.str();
            gameIO::print(str);
            // 从容器中移除lion
            red->die();
            m_warriors_red.clear();
            m_redWarriorExists = false;
        }
    }
    if (m_blueWarriorExists) {
        auto& blue = m_warriors_blue.back();
        if (blue->getLoyalty() <= 0 && blue->getType() == WarriorType::lion) {
            // std::cout << "the loyalty of " << warrior->getTypeName() << " " << warrior->getNumber() << " is 0" << std::endl;
            // e.g. 000:05 blue lion 1 ran away
            ss << std::setw(3) << std::setfill('0') << hour << ':' << std::setw(2) << std::setfill('0') << minute << ' '
               << blue->getHeadColorName() << " " << blue->getTypeName() << " " << blue->getNumber()
               << " ran away" << std::endl;
            gameIO::print(ss.str());
            // 从容器中移除lion
            blue->die();
            m_warriors_blue.clear();
            m_blueWarriorExists = false;
        }
    }
}

WarriorType AbstractCity::getRedWarriorType()
{
    return this->m_warriors_red[0]->getType();
}

WarriorType AbstractCity::getBlueWarriorType()
{
    return this->m_warriors_blue[0]->getType();
}