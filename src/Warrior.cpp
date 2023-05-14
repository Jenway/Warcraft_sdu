// src\Warrior.cpp 战士类的实现
#include "../include/Warrior.h"
#include "../include/City.h"
#include "../include/Enums.h"
#include "../include/Headquarter.h"
#include "../include/Weapon.h"
#include "../include/WeaponFactory.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

// 初始化战士的默认生命值 全部为0 ，防止调用时出错
WarriorType Warrior::m_type = WarriorType::dragon;
int Warrior::s_defaultLife[static_cast<int>(WarriorType::Count)] = { 0 };
int Warrior::s_defaultAttack[static_cast<int>(WarriorType::Count)] = { 0 };
int Lion::K_loyalty = 0;

void Warrior::attack(std::shared_ptr<Warrior> enemy)
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

void Warrior::march(int hour, int minute)
{

    auto currentCity = this->getCurrentCity();

    // 如果当前城市是敌人的司令部,则战士到达敌人司令部,游戏结束
    if (currentCity->isHeadquarter()) {
        auto current = std::dynamic_pointer_cast<Headquarter>(currentCity);
        auto temp = current->getColor();
        if (current->getColor() != this->getHeadColor()) {

            current->occupy();
            return;
        }
    }
    std::shared_ptr<AbstractCity> nextCity = currentCity->nextCity(m_headColor);
    // 从当前城市离开
    if (!currentCity->isHeadquarter()) {

        currentCity->removeWarrior(std::shared_ptr<Warrior>(this));
    }

    nextCity->addWarrior(std::shared_ptr<Warrior>(this), this->getHeadColor());

    // 派生类特性的实现
    switch (this->getType()) {
    case WarriorType::lion:
        // 每前进一步忠诚度就降低 K 忠诚度<=0 则该 lion 逃离战场,永远消失 但是已经到达敌人司令部的 lion 不会逃跑 lion 在己方司令部可能逃跑
        dynamic_cast<Lion*>(this)->decreaseLoyalty();
        if (this->getLoyalty() <= 0 && currentCity->isHeadquarter() == false) {
            dynamic_cast<Lion*>(this)->escape();
        }
        break;
    case WarriorType::wolf:
        break;
    case WarriorType::ninja:
        break;
    case WarriorType::dragon:
        break;
    case WarriorType::iceman:
        //    每前进一步,生命值减少 10%(减少的量要去尾取整)
        this->setHPviaAttack(this->getHP() / 10);
        break;
    default:
        break;
    }
    // 000:10 red iceman 1 marched to city 1 with 20 elements and force 30

    std::cout << std::setw(3) << std::setfill('0') << hour << ':' << std::setw(2) << std::setfill('0') << minute << ' ';
    std::cout << this->getHeadColorName() << ' ' << this->getTypeName() << ' ' << this->getNumber() << " marched to city " << currentCity->getCityNumber() + 1 << " with " << this->getHP() << " elements and force " << this->getAttack() << std::endl;
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

void Warrior::reportWeapon(int hour, int minute) const // 输出武器信息
{
    // e.g.
    // 000:55 blue lion 1 has 0 sword 1 bomb 0 arrow and 10 elements
    std::cout << this->getHeadColorName() << " " << this->getTypeName() << " " << this->getNumber() << " has ";
    int sword = 0, bomb = 0, arrow = 0;
    for (auto& weapon : weapons) {
        switch (weapon->getType()) {
        case WeaponType::sword:
            sword++;
            break;
        case WeaponType::bomb:
            bomb++;
            break;
        case WeaponType::arrow:
            arrow++;
            break;
        default:
            break;
        }
    }
    std::cout << sword << " sword " << bomb << " bomb " << arrow << " arrow and " << this->getHP() << " elements" << std::endl;
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
    // TODO 待修改，判断条件有问题
    // if (auto city = cityWeakPtr.lock()) { // 检查 weak_ptr 是否仍然有效
    //     city->removeWarrior(std::shared_ptr<Warrior>(this));
    // }
    // if (auto headquarter = homeWeakPtr.lock()) {
    //     headquarter->removeWarrior(std::shared_ptr<Warrior>(this));
    // }
}

void Wolf::robWeapon()
{
    std::shared_ptr<AbstractCity> city = this->currentCity;
    // 有无敌人是不用判断的
    this->enemyWeakPtr = city->getEnemy(this->getHeadColor());

    // 如果敌人是 wolf,则不抢夺
    if (enemyWeakPtr->getType() == WarriorType::wolf) {
        return;
    } else {
        // TODO enemy being robbed
        // 抢夺敌人的武器
        // 会抢到敌人编号最小的那种武器 如果敌人有多件这样的武器,则全部抢来
        // Wolf 手里武器也不能超过 10 件 如果敌人 arrow 太多没法都抢来,那就先抢没用过的
        enemyWeakPtr->sortWeapon();
        for (auto& weapon : enemyWeakPtr->getWeapons()) {
            int temp = weapon->getNumber();
            auto weaponType = weapon->getType();
        }
    }
}