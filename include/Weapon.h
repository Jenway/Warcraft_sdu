#if !defined(WEAPON_H)
#define WEAPON_H

#include <array>
#include <string>

#include "../include/Enums.h"

class Weapon {
protected:
    WeaponType m_type;
    int durability = 0;
    bool m_destroyed = false;
    bool can_be_destroyed = false;

public:
    // getter
    WeaponType getType() const { return m_type; }
    std::string getWeaponName() const { return weapon_type_name[static_cast<int>(m_type)]; }
    int getDurability() const { return durability; }
    bool isDestroyed() const { return durability == 0 && can_be_destroyed; }

    // setter
    void setDestroyed(bool destroyed) { this->m_destroyed = destroyed; }
    // decrease durability
    void decreaseDurability() { this->durability = (durability == 0) ? 0 : durability - 1; }
    // calculate damage
    virtual int enemyDamage(int attack) = 0;
    virtual int selfDamage(int attack) = 0;
    // use weapon
    bool useWeapon()
    {
        decreaseDurability();
        if (isDestroyed()) {
            setDestroyed(true);
        }
        return true;
    }
    // constructor && destructor

    Weapon() = delete;
    Weapon(WeaponType type)
        : m_type(type)
    {
    }

    virtual ~Weapon() = default;
};

class Sword : public Weapon {
public:
    Sword()
        : Weapon(WeaponType::sword)
    {
        this->can_be_destroyed = false;
    }

    int enemyDamage(int attack) override { return attack; }
    int selfDamage(int attack) override { return 0; }

    virtual ~Sword() = default;
};

class Bomb : public Weapon {
public:
    Bomb()
        : Weapon(WeaponType::bomb)
    {
        this->can_be_destroyed = true;
        this->durability = 1;
    }
    // bomb的攻击力是使用者当前攻击力的40%(去尾取整)，对使用者的攻击力是对敌人取整后的攻击力的1/2(去尾取整)。耐久一次
    int enemyDamage(int attack) override { return attack * 4 / 10; }
    int selfDamage(int attack) override { return enemyDamage(attack) / 2; }
    virtual ~Bomb() = default;
};

class Arrow : public Weapon {
public:
    Arrow()
        : Weapon(WeaponType::arrow)
    {
        this->can_be_destroyed = true;
        this->durability = 2;
    }
    // arrow的攻击力是使用者当前攻击力的30%(去尾取整)，耐久两次。
    int enemyDamage(int attack) override { return attack * 3 / 10; }
    int selfDamage(int attack) override { return 0; }
    virtual ~Arrow() = default;
};

#endif // WEAPON_H