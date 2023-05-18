// src\Warrior.cpp 战士类的实现
#include "../include/Warrior.h"
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
    // get weapon
    // TODO 在攻击时，武器会变化
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
    if (this->getType() == WarriorType::ninja && weapon->getType() == WeaponType::bomb) {

    } else {
        this->setHPviaAttack(weapon->selfDamage(attack));
    }

    weapon->useWeapon();
    // log output
    // std::cout << this->getHeadColorName() << this->getTypeName() << this->getNumber() << " attack "
    //           << enemy->getHeadColorName() << enemy->getTypeName() << enemy->getNumber() << " with " << weapon->getWeaponName() << "(" << weapon->getDurability() << ")" << std::endl;
    // std::cout << "the enemy now has " << enemy->getHP() << " elements" << std::endl;
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
    if (weapons.size() <= 1) {
        return;
    }
    // 武器顺序: sword bomb arrow
    // arrow 用过的排在前面
    // std::sort(weapons.begin(), weapons.end(), [](const std::shared_ptr<Weapon>& a, const std::shared_ptr<Weapon>& b) {
    //     if (a->getType() == WeaponType::arrow && b->getType() == WeaponType::arrow) {
    //         return a->getDurability() < b->getDurability();
    //     } else if (a->getType() == WeaponType::arrow) {
    //         return true;
    //     } else if (b->getType() == WeaponType::arrow) {
    //         return false;
    //     } else {
    //         return a->getType() < b->getType();
    //     }
    // });

    std::sort(weapons.begin(), weapons.end(), [](const std::shared_ptr<Weapon>& a, const std::shared_ptr<Weapon>& b) {
        if (a->getType() == WeaponType::arrow && b->getType() == WeaponType::arrow) {
            return a->getDurability() < b->getDurability();
        } else {
            return a->getType() < b->getType();
        }
    });
}

void Warrior::march()
{

    auto currentCity = this->getCurrentCity();

    std::shared_ptr<AbstractCity> nextCity = currentCity->nextCity(m_headColor);
    // std::cout << "the current city is " << currentCity->getCityNumber() << std::endl;
    // std::cout << "the next city is " << nextCity->getCityNumber() << std::endl;
    // 从当前城市离开
    nextCity->addWarrior(shared_from_this(), this->getHeadColor());

    currentCity->removeWarrior(this->getHeadColor(), shared_from_this());
    // std::cout << this->currentCity->getCityNumber()<<std::endl;
    // 我大概知道问题出现在哪里了，，removewarrior() 将这个武士类删除掉了，但是为什么，武士在 headquarter 的那次不会呢？
    // 至少在这次函数被调用之前，Headquarter 中都应该有这个武士类的。
    // 是shared指针的调用方式有问题，使用了 shared_from_this() 之后，就不会出现这个问题了
    setCity(nextCity); // 如果当前城市是敌人的司令部,则战士到达敌人司令部,游戏结束
    if (nextCity->isHeadquarter()) {
        auto current = std::dynamic_pointer_cast<Headquarter>(nextCity);
        if (current->getColor() != this->getHeadColor()) {
            current->occupy();
            return;
        }
    }

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
}

void Warrior::setHPviaAttack(int attack)
{
    if (attack < 0) {
        throw std::invalid_argument("attack cannot be negative");
    } else {
        m_HP = (m_HP - attack < 0) ? 0 : m_HP - attack;
    }
}

void Warrior::addWeapon(WeaponType type)
{
    auto weapon = WeaponFactory::createWeapon(type);
    weapons.emplace_back(std::move(weapon));
}

void Warrior::reportWeapon(int hour, int minute) const // 输出武器信息
{
    // e.g.
    // 000:55 blue lion 1 has 0 sword 1 bomb 0 arrow and 10 elements
    std::cout << std::setw(3) << std::setfill('0') << hour << ':' << std::setw(2) << std::setfill('0') << minute << ' ';
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
    this->m_number = 999;
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

void Wolf::snatchWeapons(std::shared_ptr<Warrior> enemy, int hour, int minute)
{
    // 如果敌人是 wolf,则不抢夺
    if (enemy->getType() == WarriorType::wolf) {
        return;
    } else {
        // TODO 抢夺敌人的武器
        // 会抢到敌人编号最小的那种武器 如果敌人有多件这样的武器,则全部抢来
        // Wolf 手里武器也不能超过 10 件 如果敌人 arrow 太多没法都抢来,那就先抢没用过的
        enemy->sortWeapon();
        for (auto i = 0; i < enemy->getWeapons().size(); i++) {
            auto weapon = enemy->getWeapons()[i];
            auto weaponType = weapon->getType();
            if (this->weapons.size() >= 10) {
                break;
            } else {
                std::cout << std::setw(3) << std::setfill('0') << hour << ':' << std::setw(2) << std::setfill('0') << minute << ' ';
                std::cout << this->getHeadColorName() << " wolf " << this->getNumber() << " took " << weapon->getWeaponName() << " from " << enemy->getHeadColorName() << " " << enemy->getTypeName() << " " << enemy->getNumber() << " in city " << this->currentCity->getCityNumber() << std::endl;
                if (weaponType == WeaponType::arrow) {
                    if (weapon->getUsed() == false) {
                        this->weapons.emplace_back(std::move(weapon));
                        enemy->removeWeapon(i);
                    }
                } else {
                    this->weapons.emplace_back(std::move(weapon));
                    enemy->removeWeapon(i);
                }
            }
        }
    }
}