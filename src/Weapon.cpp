// src\Weapon.cpp 武器类的实现

#include "../include/Weapon.h"

void Sword::attack(Warrior* self, Warrior* enemy)
{
    // sword的攻击力是使用者当前攻击力的20%(去尾取整)。
    int attack = self->getAttack() * 2 / 10;
    enemy->setHPviaAttack(attack);
}

void Bomb::attack(Warrior* self, Warrior* enemy)
{
    if (self == nullptr) {
        throw std::invalid_argument("self is nullptr");
    }
    if (enemy == nullptr) {
        throw std::invalid_argument("enemy is nullptr");
    }
    if (this->isDestroyed()) {
        return;
    }
    int attack = self->getAttack() * 4 / 10;
    enemy->setHPviaAttack(attack);
    self->setHPviaAttack(attack / 2);
    // check if weapon is destroyed
    if (this->isDestroyed()) {
        this->setDestroyed(true);
    }
}

void Arrow::attack(Warrior* self, Warrior* enemy)
{
    if (self == nullptr) {
        throw std::invalid_argument("self is nullptr");
    }
    if (enemy == nullptr) {
        throw std::invalid_argument("enemy is nullptr");
    }
    if (this->isDestroyed()) {
        return;
    }
    int attack = self->getAttack() * 3 / 10;
    enemy->setHPviaAttack(attack);
    this->decreaseDurability();
    if (this->isDestroyed()) {
        this->setDestroyed(true);
    }
}