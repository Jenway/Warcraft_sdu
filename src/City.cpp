#include "../include/City.h"
#include <memory>


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
