#include "../include/AbstractCity.h"
#include "../include/Warrior.h"
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
            warrior->setCity(std::make_shared<AbstractCity>(*this));
            m_warriors_red.push_back(std::move(warrior));
        } else {
            m_blueWarriorExists = true;
            warrior->setCity(std::make_shared<AbstractCity>(*this));
            m_warriors_blue.push_back(std::move(warrior));
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
        m_warriors_red.pop_back();
    } else {
        // 从 m_warriors_blue 中移除
        m_warriors_red.pop_back();
    }
}



// battle
void AbstractCity::battle()
{
    // 塔塔开~
    while (this->m_warriors_red[0]->isAlive() || this->m_warriors_red[0]->isAlive()) {
        this->attackOnBattle(this->m_warriors_red[0], this->m_warriors_blue[0]);
    }
}

void AbstractCity::attackOnBattle(std::shared_ptr<Warrior> warrior_on_attack, std::shared_ptr<Warrior> enemy)
{
    if (warrior_on_attack->getType() == WarriorType::wolf) {

        // warrior_on_attack->robWeapon();
        auto robbing_wolf = std::make_shared<Wolf>(warrior_on_attack);
        robbing_wolf->robWeapon();
    }
}
