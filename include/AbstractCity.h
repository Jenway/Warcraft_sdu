#if !defined(ABSTRACT_CITY_H)

#define ABSTRACT_CITY_H

#include "Enums.h"
#include "Weapon.h"
#include <memory>

class Warrior;
class AbstractCity {
protected:
    // 掉落的武器
    std::shared_ptr<Weapon> droped_weapons;

public:
    // 武器掉落与捡起相关
    void dropWeapon(std::shared_ptr<Weapon> weapon) { }
    std::shared_ptr<Weapon> pickUpWeapon() { return nullptr; }
    // battle 相关
    bool isBattle() const { return false; }

    void attackOnBattle(std::shared_ptr<Warrior> warrior_on_attack, std::shared_ptr<Warrior> enemy);
    void battle();
    // void reportWeapon() { }
    // void reportWarrior() { }
    // void reportHeadquarter() { }
    // void reportElements() { }

    // 获取需要的信息
    virtual AbstractCity& nextCity() = 0;
    virtual AbstractCity& previousCity() = 0;
    virtual bool isHeadquarter() const = 0;
    virtual void addWarrior(std::shared_ptr<Warrior> warrior, head_color color) = 0;
    virtual ~AbstractCity() = default;
};
#endif // ABSTRACT_CITY_H