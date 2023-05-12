#include "../include/City.h"
#include <memory>

void City::addWarrior(std::shared_ptr<Warrior> warrior, head_color color)
{
    // 最多只能有一个红色武士和一个蓝色武士
    if (color == head_color::red) {
        if (m_redWarriorExists) {
            return;
        } else {
            m_redWarriorExists = true;
            warrior->setWeakCityptr(std::make_shared<City>(*this));
            m_warriors_red.push_back(std::move(warrior));
        }

    } else {
        if (m_blueWarriorExists) {
            return;
        } else {
            m_blueWarriorExists = true;
            warrior->setWeakCityptr(std::make_shared<City>(*this));
            m_warriors_blue.push_back(std::move(warrior));
        }
    }
}

std::shared_ptr<Warrior> City::getEnemy(head_color color)
{

    if (color == head_color::red) {
        if (m_blueWarriorExists) {
            return m_warriors_blue.back();
        } else {
            return nullptr;
        }
    } else {
        if (m_redWarriorExists) {
            return m_warriors_red.back();
        } else {
            return nullptr;
        }
    }
}
