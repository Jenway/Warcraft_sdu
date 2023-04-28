// WarriorFactory  战士工厂类
#if !defined(WARRIORFACTORY_H)
#define WARRIORFACTORY_H

#include <memory>
#include <stdexcept>


#include "../include/Enums.h"
#include "../include/Warrior.h"

class WarriorFactory {
public:
    static std::unique_ptr<Warrior> createWarrior(WarriorType type) {
        switch (type) {
            case WarriorType::dragon:
                return std::make_unique<Dragon>();
            case WarriorType::ninja:
                return std::make_unique<Ninja>();
            case WarriorType::iceman:
                return std::make_unique<Iceman>();
            case WarriorType::lion:
                return std::make_unique<Lion>();
            case WarriorType::wolf:
                return std::make_unique<Wolf>();
            default:
                throw std::invalid_argument("Invalid warrior type");
        }
    }
};


#endif // WARRIORFACTORY_H
