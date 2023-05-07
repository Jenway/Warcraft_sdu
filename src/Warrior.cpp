// src\Warrior.cpp 战士类的实现
#include "../include/Warrior.h"
#include "../include/City.h"
#include "../include/Enums.h"
#include "../include/Headquarter.h"
#include "../include/Weapon.h"
#include "../include/WeaponFactory.h"


#include <algorithm>
#include <memory>
#include <vector>

// 初始化战士的默认生命值 全部为0 ，防止调用时出错
WarriorType Warrior::m_type = WarriorType::dragon;
int Warrior::s_defaultLife[static_cast<int>(WarriorType::Count)] = { 0 };
int Warrior::s_defaultAttack[static_cast<int>(WarriorType::Count)] = { 0 };
int Lion::K_loyalty = 0;

void ::Warrior::attack(Warrior* enemy)
{
    // check if self own weapon
    if (weapons.empty()) {
        return;
    }
    // weapon order
    // sword bomb arrow
    // order the weapons
    sortWeapon();
    // get weapon
    auto weapon = weapons[0].get();
    while (weapon->isDestroyed()) {
        weapons.erase(weapons.begin());
        weapon = weapons[0].get();
    }

    // check if enemy is dead
    if (enemy->getHP() == 0) {
        return;
    }
    // get attack and use weapon
    int attack = this->getAttack();

    enemy->setHPviaAttack(weapon->enemyDamage(attack));
    if (this->getType() != WarriorType::ninja) {
        this->setHPviaAttack(weapon->selfDamage(attack));
    }
    weapon->useWeapon();
    if (weapon->isDestroyed()) {
        weapons.erase(weapons.begin());
    }

    // check if enemy is dead
    if (enemy->getHP() == 0) {
        enemy->setDead();
    }
    // check if self is dead
    if (this->getHP() == 0) {
        this->setDead();
    }
}

void Warrior::sortWeapon()
{
    // 战斗开始前,根据武器编号从小到大排列使用顺序,用过的arrow排在未用过的前面,战斗中不会重新排列。
    std::sort(weapons.begin(), weapons.end(), [](const std::shared_ptr<Weapon>& a, const std::shared_ptr<Weapon>& b) {
        if (a->getType() == WeaponType::arrow && b->getType() == WeaponType::arrow) {
            return a->getDurability() < b->getDurability();
        } else if (a->getType() == WeaponType::arrow) {
            return true;
        } else if (b->getType() == WeaponType::arrow) {
            return false;
        } else {
            return a->getType() < b->getType();
        }
    });
}

void Warrior::march()
{
    AbstractCity& currentCity = this->getCurrentCity();
    AbstractCity& nextCity = currentCity.nextCity();
    // check if next city is enemy's headquarter
    if (nextCity.isHeadquarter()) {
        // TODO
    } else {
        // TODO
        nextCity.addWarrior(std::shared_ptr<Warrior>(this), this->getHeadColor());
    }
}

void Warrior::setHPviaAttack(int attack)
{
    if (attack < 0) {
        throw std::invalid_argument("attack cannot be negative");
    } else {
        m_HP = (m_HP - attack < 0) ? 0 : m_HP - attack;
    }
}

void Warrior::addWeapon(WeaponType type, int attack, int number)
{
    auto weapon = WeaponFactory::createWeapon(type, attack);
    weapon->setNumber(number);
    weapons.emplace_back(std::move(weapon));
}

Warrior::Warrior()
{
    // 示例输出 000 red iceman 1 born with strength 5,1 iceman in red headquarter
    this->m_type = WarriorType::dragon;
    this->m_number = 1;
    this->m_HP = 5;
    this->m_attack = 5;
    this->m_headColor = head_color::red;
}

Warrior::Warrior(WarriorType type, int number, head_color color)
{
    m_type = type;
    this->m_HP = s_defaultLife[static_cast<int>(type)];
    this->m_attack = s_defaultAttack[static_cast<int>(type)];
    this->m_number = number;
    this->m_headColor = color;
}

Warrior::~Warrior()
{
    if (auto city = cityWeakPtr.lock()) { // 检查 weak_ptr 是否仍然有效
        city->removeWarrior(std::shared_ptr<Warrior>(this));
    }
    if (auto headquarter = homeWeakPtr.lock()) {
        headquarter->removeWarrior(std::shared_ptr<Warrior>(this));
    }
}
