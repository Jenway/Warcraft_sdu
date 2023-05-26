// src\Warrior.cpp 战士类的实现
#include "../include/Warrior.h"
#include "../include/Enums.h"
#include "../include/GameIO.h"
#include "../include/Headquarter.h"
#include "../include/Weapon.h"
#include "../include/WeaponFactory.h"


#include <algorithm>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

// 初始化战士的默认生命值 全部为0 ，防止调用时出错
int Warrior::s_defaultLife[static_cast<int>(WarriorType::Count)] = { 0 };
int Warrior::s_defaultAttack[static_cast<int>(WarriorType::Count)] = { 0 };
int Lion::K_loyalty = 0;

void Warrior::attack(std::shared_ptr<Warrior> enemy)
{
    // bool DEBUG = false;
    // if (this->getNumber() == 6 && enemy->getNumber() == 8) {
    //     DEBUG = true;
    // }
    bool onAttack = true;
    while (onAttack) {
        // check if self is dead or self own weapon
        if (this->getHP() == 0 || enemy->getHP() == 0 || weapons.empty()) {
            return;
        }
        auto weapon = weapons[this->m_currentWeaponIndex].get();
        WeaponType weaponType = weapon->getType();

        int attack = this->getAttack();

        enemy->setHPviaAttack(weapon->enemyDamage(attack));
        if (this->getType() == WarriorType::ninja && weapon->getType() == WeaponType::bomb) {
        } else {
            this->setHPviaAttack(weapon->selfDamage(attack));
        }

        weapon->useWeapon();
        if (weapon->isDestroyed()) {
            weapons.erase(weapons.begin() + this->m_currentWeaponIndex);
        }

        if (weapons.empty()) {
            this->m_currentWeaponIndex = 0;
            onAttack = false;
        }
        // 这个武器使用的实验要求说的不是很清楚
        int temp = this->m_currentWeaponIndex + 1;
        if (temp >= weapons.size()) {
            this->m_currentWeaponIndex = 0;
            onAttack = false;
        } else {
            this->m_currentWeaponIndex = temp;
            if (weapons[this->m_currentWeaponIndex]->getType() == weaponType) {
                onAttack = false;
            } else {
                onAttack = false;
            }
        }

        // check if enemy is dead
        if (enemy->getHP() == 0) {
            enemy->setDead();
        }
        // check if self is dead
        if (this->getHP() == 0) {
            this->setDead();
        }
        // now the warrior color type and number and weapon and durability is as blelos
        // std::cout << this->getHeadColorName() << " " << this->getTypeName() << " " << this->getNumber() << " attacked " << enemy->getHeadColorName() << " " << enemy->getTypeName() << " " << enemy->getNumber() << " with " << weapon->getWeaponName() << "(" << weapon->getDurability() << ")" << std::endl;

        // get attack and use weapon

        // log output
        // std::cout << this->getHeadColorName() << this->getTypeName() << this->getNumber() << " attack "
        //           << enemy->getHeadColorName() << enemy->getTypeName() << enemy->getNumber() << " with " << weapon->getWeaponName() << "(" << weapon->getDurability() << ")" << std::endl;
        // std::cout << "the enemy now has " << enemy->getHP() << " elements" << std::endl;
    }
}
void Warrior::sortWeapon()
{
    this->m_currentWeaponIndex = 0;

    // 战斗开始前,根据武器编号从小到大排列使用顺序,用过的arrow排在未用过的前面,战斗中不会重新排列。
    if (weapons.size() <= 1) {
        return;
    }
    // 武器顺序: sword bomb arrow(用过的排在前面)

    std::sort(weapons.begin(), weapons.end(), [](const std::shared_ptr<Weapon>& a, const std::shared_ptr<Weapon>& b) {
        if (a->getType() == WeaponType::arrow && b->getType() == WeaponType::arrow) {
            return a->getDurability() < b->getDurability();
        } else {
            return a->getType() < b->getType();
        }
    });
}

bool Warrior::unchanged()
{
    bool unchanged = true;
    for (auto& weapon : weapons) {
        if (weapon->enemyDamage(this->m_attack) > 0) {
            unchanged = false;
            break;
        }
    }
    return unchanged;
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
    // 我大概知道问题出现在哪里了，，removewarrior() 将这个武士类删除掉了，但是为什么，武士在 headquarter 的那次不会呢？
    // 至少在这次函数被调用之前，Headquarter 中都应该有这个武士类的。
    // 是shared指针的调用方式有问题，使用了 shared_from_this() 之后，就不会出现这个问题了
    setCity(nextCity);
    // 派生类特性的实现
    switch (this->getType()) {
    case WarriorType::lion:
        // 每前进一步忠诚度就降低 K 忠诚度<=0 则该 lion 逃离战场,永远消失 但是已经到达敌人司令部的 lion 不会逃跑 lion 在己方司令部可能逃跑
        dynamic_cast<Lion*>(this)->decreaseLoyalty();
        if (this->getLoyalty() <= 0 && nextCity->isHeadquarter() == true) {
            this->setLoyalty(1);
        }
        break;
    case WarriorType::iceman:
        //    每前进一步,生命值减少 10%(减少的量要去尾取整)
        this->setHPviaAttack(this->getHP() / 10);
        break;
    default:
        break;
    }
    if (nextCity->isHeadquarter()) {
        auto current = std::dynamic_pointer_cast<Headquarter>(nextCity);
        if (current->getColor() != this->getHeadColor()) {
            current->occupy();
            return;
        }
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

void Warrior::pickWeapons(std::shared_ptr<Warrior> enemy)
{

    auto enemy_weapons = enemy->getWeapons();
    // 如果敌人没有武器,则不抢夺
    if (enemy_weapons.empty()) {
        return;
    }
    // 排序 武器顺序: sword bomb arrow 其中 arrow 没用过的排在前面
    std::sort(enemy_weapons.begin(), enemy_weapons.end(), [](const std::shared_ptr<Weapon>& a, const std::shared_ptr<Weapon>& b) {
        if (a->getType() == WeaponType::arrow && b->getType() == WeaponType::arrow) {
            return a->getDurability() > b->getDurability();
        } else {
            return a->getType() < b->getType();
        }
    });
    // 武器不能超过 10 个，同一种武器可以拿多个
    WeaponType weaponType = enemy_weapons[0]->getType();
    for (auto i = 0; i < enemy_weapons.size(); i++) {
        auto weapon = enemy_weapons[i];
        if (weapon->getType() == weaponType) {
            if (this->weapons.size() >= 10) {
                break;
            }
            this->weapons.emplace_back(std::move(weapon));
        }
    }
}

void Warrior::reportWeapon(int hour, int minute) const // 输出武器信息
{
    std::stringstream ss;
    // 000:55 blue lion 1 has 0 sword 1 bomb 0 arrow and 10 elements
    ss << std::setw(3) << std::setfill('0') << hour << ':' << std::setw(2) << std::setfill('0') << minute << ' ';
    ss << this->getHeadColorName() << " " << this->getTypeName() << " " << this->getNumber() << " has ";
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
    ss << sword << " sword " << bomb << " bomb " << arrow << " arrow and " << this->getHP() << " elements" << std::endl;
    gameIO::print(ss.str());
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
    // TODO 待修改
}

void Wolf::snatchWeapons(std::shared_ptr<Warrior> enemy, int hour, int minute)
{
    std::stringstream ss;
    // 如果敌人是 wolf,则不抢夺
    if (enemy->getType() == WarriorType::wolf) {
        return;
    } else {
        // TODO 抢夺敌人的武器
        // 会抢到敌人编号最小的那种武器 如果敌人有多件这样的武器,则全部抢来
        // Wolf 手里武器也不能超过 10 件 如果敌人 arrow 太多没法都抢来,那就先抢没用过的
        auto enemy_weapons = enemy->getWeapons();
        // 如果敌人没有武器,则不抢夺
        if (enemy_weapons.empty()) {
            return;
        }
        // 排序 武器顺序: sword bomb arrow 其中 arrow 没用过的排在前面
        std::sort(enemy_weapons.begin(), enemy_weapons.end(), [](const std::shared_ptr<Weapon>& a, const std::shared_ptr<Weapon>& b) {
            if (a->getType() == WeaponType::arrow && b->getType() == WeaponType::arrow) {
                return a->getDurability() > b->getDurability();
            } else {
                return a->getType() < b->getType();
            }
        });
        WeaponType weaponType = enemy_weapons[0]->getType();
        std::string weaponTypeName = weapon_type_name[static_cast<int>(weaponType)];
        int tookWeaponNum = 0;

        // 标记需要删除的武器的索引
        std::vector<int> indicesToRemove;

        // 遍历敌人的武器并标记需要删除的武器
        for (int i = 0; i < enemy->getWeapons().size(); i++) {
            auto weapon = enemy->getWeapons()[i];
            if (weapon->getType() == weaponType) {
                if (this->weapons.size() >= 10) {
                    break;
                }
                this->weapons.emplace_back(std::move(weapon));
                tookWeaponNum++;
                indicesToRemove.push_back(i);
            }
        }

        // 从后向前删除被拿走的武器
        for (int i = indicesToRemove.size() - 1; i >= 0; i--) {
            int indexToRemove = indicesToRemove[i];
            enemy->eraseWeapon(indexToRemove);
        }

        ss << std::setw(3) << std::setfill('0') << hour << ':' << std::setw(2) << std::setfill('0') << minute << ' ';
        ss << this->getHeadColorName() << " wolf " << this->getNumber() << " took " << tookWeaponNum << " " << weaponTypeName << " from " << enemy->getHeadColorName() << " " << enemy->getTypeName() << " " << enemy->getNumber() << " in city " << this->currentCity->getCityNumber() << std::endl;
        gameIO::print(ss.str());
    }
}