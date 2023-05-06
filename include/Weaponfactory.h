#if !defined(WEAPONFACTORY_H)
#define WEAPONFACTORY_H

#include <memory>
#include <stdexcept>

#include "../include/Enums.h"
#include "../include/Weapon.h"

class WeaponFactory {
public:
    static std::unique_ptr<Weapon> createWeapon(WeaponType type, int attack)
    {
        switch (type) {
        case WeaponType::sword:
            return std::make_unique<Sword>(attack);
        case WeaponType::bomb:
            return std::make_unique<Bomb>(attack);
        case WeaponType::arrow:
            return std::make_unique<Arrow>(attack);
        default:
            throw std::invalid_argument("Invalid weapon type");
        }
    }
};

#endif