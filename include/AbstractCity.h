#include <cstddef>
#include <type_traits>
#if !defined(ABSTRACT_CITY_H)

#define ABSTRACT_CITY_H

#include "Enums.h"
#include "Weapon.h"
#include <memory>
#include <vector>

class Warrior;
class AbstractCity : public std::enable_shared_from_this<AbstractCity> {
protected:
    // 在这个城市掉落的武器
    std::vector<std::shared_ptr<Weapon>> weapons;
    // 在这个城市的武士
    std::shared_ptr<Warrior> m_warriors_blue;
    std::shared_ptr<Warrior> m_warriors_red;
    // 状态，是否有红蓝武士
    bool m_redWarriorExists = false;
    bool m_blueWarriorExists = false;
    // neighbor
    std::shared_ptr<AbstractCity> m_leftCity;
    std::shared_ptr<AbstractCity> m_rightCity;
    // 判断是否是 headquater
    bool isThisHeadquater = false;

public:
    // set neighbor
    void setLeftCity(std::shared_ptr<AbstractCity> city) { m_leftCity = city; }
    void setRightCity(std::shared_ptr<AbstractCity> city) { m_rightCity = city; }
    // 返回下一个城市的shared_ptr
    virtual std::shared_ptr<AbstractCity> nextCity(head_color warrior_color) { return nullptr; }
    virtual std::shared_ptr<AbstractCity> previousCity() { return nullptr; }
    // 返回城市编号
    virtual int getCityNumber() { return 0; }
    // 状态返回
    bool isBattle() { return m_redWarriorExists && m_blueWarriorExists; }

    // 武器掉落与捡起相关
    void dropWeapon(std::shared_ptr<Weapon> weapon) { weapons.push_back(weapon); }
    std::shared_ptr<Weapon> pickUpWeapon() { return nullptr; }
    // battle 相关
    void battle();
    void attackOnBattle(std::shared_ptr<Warrior> red, std::shared_ptr<Warrior> blue);

    // 武士相关
    void reportWeapon(int hour, int minute);
    // 输入敌人颜色，返回对应的武士
    std::shared_ptr<Warrior> getEnemy(head_color color);

    bool isHeadquarter() { return this->isThisHeadquater; }
    void addWarrior(std::shared_ptr<Warrior> warrior, head_color color);
    // 是否存在对应颜色的武士
    bool hasWarrior(head_color color);
    void removeWarrior(head_color color);
    virtual ~AbstractCity() = default;
};
#endif // ABSTRACT_CITY_H