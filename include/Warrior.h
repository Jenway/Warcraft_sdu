// Warrior 战士类
#if !defined(WARRIOR_H)
#define WARRIOR_H

#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

#include "../include/Enums.h"
#include "../include/Weapon.h"
// 定义战士类
class Warrior {
protected:
    static WarriorType m_type;
    static int s_defaultLife[static_cast<int>(WarriorType::Count)]; // 默认生命值

    int m_life = 0;
    int m_number = 0;

    std::vector<std::unique_ptr<Weapon>> weapons;

public:
    // getter
    int getNumber() const { return this->m_number; }
    int getLife() const { return m_life; }
    static int getLifeCost(int index) { return s_defaultLife[index]; }

    WarriorType getType() const { return m_type; }
    std::string getTypeName() const { return warrior_type_name[static_cast<int>(m_type)]; }
    Weapon* getWeapon(int index) const { return weapons[index].get(); }
    // setter
    static void setDefaultLife(WarriorType type, int life) { s_defaultLife[static_cast<int>(type)] = life; }
    void setNumber(int number) { m_number = number; }

    // add weapon
    void addWeapon(WeaponType type, int attack, int number);

    // indicate whether the warrior is dead
    bool isDead() const { return m_life <= 0; }

    // for deived class to override

    // virtual void printBorn() const = 0;
    // virtual void printWeapon() const = 0;
    // virtual void printYell() const = 0;
    // virtual void printMarch() const = 0;

    // getter
    virtual double getMorale() const { return 0.0; }
    virtual int getLoyalty() const { return 0; }

    // setter
    virtual void setMorale(double morale) { }
    virtual void setLoyalty(int loyalty) { }

    // constructor && destructor
    Warrior();
    Warrior(WarriorType type, int number);

    ~Warrior();
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
};

class Ninja : public Warrior {
public:
    Ninja(int number)
        : Warrior(WarriorType::ninja, number)
    {
        addWeapon(static_cast<WeaponType>(this->m_number % 3), 0, 0);
        addWeapon(static_cast<WeaponType>(this->m_number % 3 + 1), 0, 0);
    }
};

class Iceman : public Warrior {
public:
    Iceman(int number)
        : Warrior(WarriorType::iceman, number)
    {
        addWeapon(static_cast<WeaponType>(this->m_number % 3), 0, 0);
    }
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
};

class Wolf : public Warrior {
public:
    Wolf(int number)
        : Warrior(WarriorType::wolf, number)
    {
    }
};

#endif // WARRIOR_H