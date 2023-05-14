#if !defined(CITY_H)
#define CITY_H

#include <iostream>
#include <memory>
#include <vector>

// #include "../include/Enums.h"
#include "../include/AbstractCity.h"
#include "../include/Warrior.h"

class City : public AbstractCity {

private:
    int cityNumber = 0;

public:
    // override

    std::shared_ptr<AbstractCity> nextCity(head_color color) override
    {
        if (color == head_color::red) {
            return m_rightCity;
        } else {
            return m_leftCity;
        }
    }
    std::shared_ptr<AbstractCity> previousCity() override
    {
        return nullptr;
    }

    // void addWarrior(std::shared_ptr<Warrior> warrior, head_color color);

    // Function for getting the number of warriors in the city
    int getWarriorCount() { return m_warriors_blue.size() + m_warriors_red.size(); }

    // Function for getting the number of the city
    int getCityNumber() override { return cityNumber; }

    // Function for getting the team of the warrior in the city (returns NONE if there is no warrior)
    head_color getWarriorTeam()
    {
        if (m_redWarriorExists && !m_blueWarriorExists) {
            return head_color::red;
        } else if (!m_redWarriorExists && m_blueWarriorExists) {
            return head_color::blue;
        } else {
            return head_color::Count;
        }
    }
    // 事件处理函数
    // 获取敌人
    std::shared_ptr<Warrior> getEnemy(head_color color);
    // 战斗
    City(int number)
        : cityNumber(number)
    {
        this->isThisHeadquater = false;
    }
    virtual ~City() { }
};

#endif
