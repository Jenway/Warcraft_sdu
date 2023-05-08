#include "../include/AbstractCity.h"
#include "../include/Warrior.h"
#include <memory>

void AbstractCity::battle()
{
    // 塔塔开~
    // 首先找到红色武士和蓝色武士
    std::shared_ptr<Warrior> redWarrior = nullptr;
    std::shared_ptr<Warrior> blueWarrior = nullptr;

    while (redWarrior->isAlive() || blueWarrior->isAlive()) {
        this->attackOnBattle(redWarrior, blueWarrior);
    }
}

void AbstractCity::attackOnBattle(std::shared_ptr<Warrior> warrior_on_attack, std::shared_ptr<Warrior> enemy)
{
    if (warrior_on_attack->getType() == WarriorType::wolf) {

        // warrior_on_attack->robWeapon();
        auto robbing_wolf = std::make_shared<Wolf>(warrior_on_attack);
        robbing_wolf->robWeapon(enemy);
    }
}