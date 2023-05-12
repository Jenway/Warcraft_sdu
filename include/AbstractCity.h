#if !defined(ABSTRACT_CITY_H)

#define ABSTRACT_CITY_H

#include "Enums.h"
#include "Weapon.h"
#include <memory>
#include <vector>

class Warrior;
class AbstractCity {
protected:
    // 在这个城市掉落的武器
    std::vector<std::shared_ptr<Weapon>> weapons;
    // 在这个城市的武士
    std::vector<std::shared_ptr<Warrior>> m_warriors_blue;
    std::vector<std::shared_ptr<Warrior>> m_warriors_red;
    // 状态，是否有红蓝武士
    bool m_redWarriorExists = false;
    bool m_blueWarriorExists = false;

public:
    // 状态返回
    bool isBattle() { return m_redWarriorExists && m_blueWarriorExists; }
    // 武器掉落与捡起相关
    void dropWeapon(std::shared_ptr<Weapon> weapon) { weapons.push_back(weapon); }
    std::shared_ptr<Weapon> pickUpWeapon() { return nullptr; }
    // battle 相关
    void battle();
    void attackOnBattle(std::shared_ptr<Warrior> warrior_on_attack, std::shared_ptr<Warrior> enemy);

    // 返回下一个城市的shared_ptr
    virtual std::shared_ptr<AbstractCity> nextCity() { return nullptr; }
    virtual std::shared_ptr<AbstractCity> previousCity() { return nullptr; }
    virtual bool isHeadquarter() { return false; }
    void addWarrior(std::shared_ptr<Warrior> warrior, head_color color);
    // 是否存在对应颜色的武士
    bool hasWarrior(head_color color);
    void removeWarrior(std::shared_ptr<Warrior> warrior);
    virtual ~AbstractCity() = default;
};
#endif // ABSTRACT_CITY_H