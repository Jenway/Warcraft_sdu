#if !defined(WEAPON_H)
#define WEAPON_H

#include <array>
#include <string>

#include "../include/Enums.h"
#include "../include/Warrior.h"

class Weapon {
protected:
    WeaponType m_type;
    int m_attack = 0;
    int m_number = 0;
    int durability = 0;
    bool m_destroyed = false;
    bool can_be_destroyed = false;

public:
    // getter
    WeaponType getType() const { return m_type; }
    std::string getName() const { return weapon_type_name[static_cast<int>(m_type)]; }
    int getAttack() const { return m_attack; }
    int getNumber() const { return m_number; }
    int getDurability() const { return durability; }
    bool getCanBeDestroyed() const { return can_be_destroyed; }
    bool isDestroyed() const { return durability == 0 && can_be_destroyed; }

    // setter
    void setAttack(int attack) { this->m_attack = attack; }
    void setDurability(int durability) { this->durability = durability; }
    void setCanBeDestroyed(bool can_be_destroyed) { this->can_be_destroyed = can_be_destroyed; }
    void setNumber(int number) { this->m_number = number; }
    void setDestroyed(bool destroyed) { this->m_destroyed = destroyed; }
    // decrease durability
    void decreaseDurability() { this->durability = (durability == 0) ? 0 : durability - 1; }
    // Attack
    virtual void attack(Warrior* self, Warrior* enemy) = 0;
    // constructor && destructor

    Weapon(WeaponType type, int attack, int number = 0)
        : m_type(type)
        , m_attack(attack)
        , m_number(number)
    {
    }

    virtual ~Weapon() = default;
};

class Sword : public Weapon {
public:
    Sword(int attack)
        : Weapon(WeaponType::sword, attack, 0)
    {
        setCanBeDestroyed(can_be_destroyed = false);
    }

    void attack(Warrior* self, Warrior* enemy) override;

    virtual ~Sword() = default;
};

class Bomb : public Weapon {
public:
    Bomb(int attack)
        : Weapon(WeaponType::bomb, attack)
    {
        setCanBeDestroyed(can_be_destroyed = true);
        setDurability(1);
    }
    // bomb的攻击力是使用者当前攻击力的40%(去尾取整)，对使用者的攻击力是对敌人取整后的攻击力的1/2(去尾取整)。耐久一次
    void attack(Warrior* self, Warrior* enemy) override;
    virtual ~Bomb() = default;
};

class Arrow : public Weapon {
public:
    Arrow(int attack)
        : Weapon(WeaponType::arrow, attack)
    {
        setCanBeDestroyed(can_be_destroyed = true);
        setDurability(2);
    }
    // arrow的攻击力是使用者当前攻击力的30%(去尾取整)，耐久两次。
    void attack(Warrior* self, Warrior* enemy) override;
    virtual ~Arrow() = default;
};

#endif // WEAPON_H