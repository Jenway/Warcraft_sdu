// Warrior 战士类
#if !defined(WARRIOR_H)
#define WARRIOR_H

#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

#include "../include/Enums.h"

// #include "../include/Weapon.h"
// 不用包含Weapon.h，因为Weapon.h中包含了Warrior.h，会造成循环包含
// 改为前向声明
class Weapon;

// 定义战士类
class Warrior {
protected:
    static WarriorType m_type;
    static int s_defaultLife[static_cast<int>(WarriorType::Count)]; // 默认生命值

    int m_HP = 0;
    int m_number = 0;
    int m_attack = 0;

    std::vector<std::unique_ptr<Weapon>> weapons;

public:
    // getter
    int getNumber() const { return this->m_number; }
    int getHP() const { return m_HP; }
    int getAttack() const { return m_attack; }
    static int getLifeCost(int index) { return s_defaultLife[index]; }

    WarriorType getType() const { return m_type; }
    std::string getTypeName() const { return warrior_type_name[static_cast<int>(m_type)]; }
    Weapon* getWeapon(int index) const { return weapons[index].get(); }
    // setter
    static void setDefaultLife(WarriorType type, int life) { s_defaultLife[static_cast<int>(type)] = life; }
    void setNumber(int number) { m_number = number; }
    void setAttack(int attack) { m_attack = attack; }
    void setHPviaAttack(int attack);
    // add weapon
    void addWeapon(WeaponType type, int attack, int number);

    // indicate whether the warrior is dead
    bool isDead() const { return m_HP <= 0; }

    // for deived class to override

    // getter
    virtual double getMorale() const { return 0.0; }
    virtual int getLoyalty() const { return 0; }

    // setter
    virtual void setMorale(double morale) { }
    virtual void setLoyalty(int loyalty) { }

    // constructor && destructor
    Warrior();
    Warrior(WarriorType type, int number);

    virtual ~Warrior();
};

// 定义具体的战士类
class Dragon : public Warrior {
private:
    double morale = 0.0;

public:
    // getter
    double getMorale() const { return morale; }
    // setter
    void setMorale(double morale) { this->morale = morale; }

    Dragon(int number)
        : Warrior(WarriorType::dragon, number)
    {
        addWeapon(static_cast<WeaponType>(this->m_number % 3), 0, 0);
    }
    virtual ~Dragon() = default;
};

class Ninja : public Warrior {
public:
    Ninja(int number)
        : Warrior(WarriorType::ninja, number)
    {
        addWeapon(static_cast<WeaponType>(this->m_number % 3), 0, 0);
        addWeapon(static_cast<WeaponType>(this->m_number % 3 + 1), 0, 0);
    }
    virtual ~Ninja() = default;
};

class Iceman : public Warrior {
public:
    Iceman(int number)
        : Warrior(WarriorType::iceman, number)
    {
        addWeapon(static_cast<WeaponType>(this->m_number % 3), 0, 0);
    }
    virtual ~Iceman() = default;
};

class Lion : public Warrior {
private:
    int loyalty = 0;

public:
    // getter
    int getLoyalty() const { return loyalty; }
    // setter
    void setLoyalty(int loyalty) { this->loyalty = loyalty; }

    Lion(int number)
        : Warrior(WarriorType::lion, number)
    {
    }
    virtual ~Lion() = default;
};

class Wolf : public Warrior {
public:
    Wolf(int number)
        : Warrior(WarriorType::wolf, number)
    {
    }
    virtual ~Wolf() = default;
};

#endif // WARRIOR_H