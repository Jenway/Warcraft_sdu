#if !defined(WEAPON_H)
#define WEAPON_H

#include <array>
#include <string>

#include "../include/Enums.h"

class Weapon {
protected:
    WeaponType m_type;
    int m_attack = 0;
    int m_number = 0;

public:
    // getter
    WeaponType getType() const { return m_type; }
    std::string getName() const
    {
        return weapon_type_name[static_cast<int>(m_type)];
    }
    int getAttack() const { return m_attack; }
    int getNumber() const { return m_number; }
    // setter
    void setNumber(int number) { m_number = number; }
    // constructor && destructor

    Weapon() = default;
    ~Weapon() = default;
};

class Sword : public Weapon {
public:
    Sword()
    {
        m_type = WeaponType::sword;
        m_attack = 0;
    }
};

class Bomb : public Weapon {
public:
    Bomb()
    {
        m_type = WeaponType::bomb;
        m_attack = 0;
    }
};

class Arrow : public Weapon {
public:
    Arrow()
    {
        m_type = WeaponType::arrow;
        m_attack = 0;
    }
};

#endif // WEAPON_H