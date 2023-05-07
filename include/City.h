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
    std::vector<std::shared_ptr<Warrior>> m_warriors_blue;
    std::vector<std::shared_ptr<Warrior>> m_warriors_red;
    bool m_redWarriorExists = false;
    bool m_blueWarriorExists = false;

public:
    // override
    AbstractCity& nextCity() override { return *this; }
    AbstractCity& previousCity() override { return *this; }
    bool isHeadquarter() const override { return false; }

    // Function for adding a warrior to the city

    void addWarrior(std::shared_ptr<Warrior> warrior, head_color color) override
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

    // Function for removing a warrior from the city
    void removeWarrior(std::shared_ptr<Warrior> warrior)
    {
        if (warrior->getHeadColor() == head_color::red) {
            // 从 m_warriors_red 中移除
        } else {
            // 从 m_warriors_blue 中移除
        }
    }

    // Function for getting the number of warriors in the city
    int getWarriorCount()
    {
        return m_warriors_blue.size() + m_warriors_red.size();
    }

    // Function for getting the number of the city
    int getCityNumber()
    {
        return cityNumber;
    }

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

    // Function for getting a pointer to the last warrior in the vector
    // Warrior* getLastWarrior()
    // {
    //     return m_warriors.back().get();
    // }

    City(int number)
    {
        cityNumber = number;
    }
    virtual ~City() { }
};

#endif
