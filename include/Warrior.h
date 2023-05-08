// Warrior 战士类
#if !defined(WARRIOR_H)
#define WARRIOR_H

#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

#include "../include/Enums.h"
// #include "../include/City.h"
// 不用包含City.h，因为City.h中包含了Warrior.h，会造成循环包含
// 改为前向声明
class City;
class Headquarter;
#include "../include/Weapon.h"
// 不用包含Weapon.h，因为Weapon.h中包含了Warrior.h，会造成循环包含
// 改为前向声明,但是前向声明不够，因为需要使用智能指针，而智能指针需要完整的类定义
// 改为实现一个抽象接口类IWeapon.h
// 然后又放弃了 :(
#include "../include/AbstractCity.h"

// 定义战士类
class Warrior {
protected:
    static WarriorType m_type;
    static int s_defaultLife[static_cast<int>(WarriorType::Count)]; // 默认生命值
    static int s_defaultAttack[static_cast<int>(WarriorType::Count)]; // 默认攻击力

    int m_HP = 0;
    int m_number = 0;
    int m_attack = 0;
    head_color m_headColor = head_color::red;
    bool m_isAlive = true;
    //  战士所在城市
    std::shared_ptr<AbstractCity> currentCity;
    std::weak_ptr<City> cityWeakPtr; // 添加 weak_ptr
    std::weak_ptr<Headquarter> homeWeakPtr; // headquarter 的 weak_ptr
    std::weak_ptr<AbstractCity> absCityWeakPtr; // 添加 abstractweak_ptr

    std::weak_ptr<Warrior> enemyWeakPtr; // 添加 weak_ptr
    std::vector<std::shared_ptr<Weapon>> weapons;

public:
    // getter
    int getNumber() const { return this->m_number; }
    int getHP() const { return m_HP; }
    int getAttack() const { return m_attack; }
    head_color getHeadColor() const { return m_headColor; }
    std::string getHeadColorName() const { return (m_headColor == head_color::red) ? "red" : "blue"; }
    AbstractCity& getCurrentCity() const { return *currentCity; }
    bool isAlive() const { return m_isAlive; }
    static int getLifeCost(int index) { return s_defaultLife[index]; }

    WarriorType getType() const { return m_type; }
    std::string getTypeName() const { return warrior_type_name[static_cast<int>(m_type)]; }
    // 改为返回智能指针
    std::shared_ptr<Weapon>& getWeapon(int index) { return weapons[index]; }
    // 事件接口
    void reportWeapon(int hour, int minute) const;
    // setter
    static void setDefaultLife(WarriorType type, int life) { s_defaultLife[static_cast<int>(type)] = life; }
    static void setDefaultAttack(WarriorType type, int attack) { s_defaultAttack[static_cast<int>(type)] = attack; }
    void setNumber(int number) { m_number = number; }
    void setAttack(int attack) { m_attack = attack; }
    void setHPviaAttack(int attack);
    void setHeadColor(head_color headColor) { m_headColor = headColor; }
    void setDead() { m_isAlive = false; }

    // 与城市交互
    void setWeakCityptr(std::weak_ptr<City> cityWeakPtr) { this->cityWeakPtr = cityWeakPtr; }
    void setHomeWeakPtr(std::weak_ptr<Headquarter> homeWeakPtr) { this->homeWeakPtr = homeWeakPtr; }
    bool operator==(const Warrior& other) const
    {
        return this->m_number == other.m_number;
    }
    // TODO 武器排序
    void
    sortWeapon();
    // 战士攻击
    void attack(std::shared_ptr<Warrior> enemy);

    // add weapon
    void addWeapon(WeaponType type, int attack, int number);
    // TODO 击败敌人后获得武器 智能指针
    // void addWeapon(Weapon* weapon) { weapons.emplace_back(weapon); }
    void addWeapon(std::unique_ptr<Weapon>& weapon) { weapons.emplace_back(std::move(weapon)); }
    // TODO 战士死亡后掉落武器
    void dropWeapon() { weapons.clear(); }
    // TODO 战士前进
    void march();

    // indicate whether the warrior is dead
    bool isDead() const { return m_HP <= 0; }

    // for deived class to override

    // getter
    virtual double getMorale() const { return 0.0; }
    virtual int getLoyalty() const { return 0; }

    // setter
    virtual void setMorale(double morale) { }
    virtual void setLoyalty(int loyalty) { }

    // constructor && destructor
    Warrior();
    Warrior(WarriorType type, int number, head_color color);

    virtual ~Warrior();
};

// 定义具体的战士类
class Dragon : public Warrior {
private:
    double morale = 0.0;

public:
    // getter
    double getMorale() const override { return morale; }
    // setter
    void setMorale(double morale) override { this->morale = morale; }

    // TODO 特有方法
    void yell() const
    {
        std::cout << "Yell" << std::endl;
    }

    Dragon(int number, head_color color)
        : Warrior(WarriorType::dragon, number, color)
    {
        addWeapon(static_cast<WeaponType>(this->m_number % 3), 0, 0);
    }
    virtual ~Dragon() = default;
};

class Ninja : public Warrior {
public:
    // 特有属性
    // 使用 bomb 不受伤害
    // 直接在 warrior 中的 attack 加个判断得了...
    Ninja(int number, head_color color)
        : Warrior(WarriorType::ninja, number, color)
    {
        addWeapon(static_cast<WeaponType>(this->m_number % 3), 0, 0);
        addWeapon(static_cast<WeaponType>(this->m_number % 3 + 1), 0, 0);
    }
    virtual ~Ninja() = default;
};

class Iceman : public Warrior {
public:
    // 特有方法
    // TODO 每前进一步生命值减少10 %
    Iceman(int number, head_color color)
        : Warrior(WarriorType::iceman, number, color)
    {
        addWeapon(static_cast<WeaponType>(this->m_number % 3), 0, 0);
    }
    virtual ~Iceman() = default;
};

class Lion : public Warrior {
private:
    int loyalty = 0;
    static int K_loyalty; // 每前进一步忠诚度减少 K

public:
    // getter
    int getLoyalty() const { return loyalty; }
    // setter
    void setLoyalty(int loyalty) { this->loyalty = loyalty; }

    // TODO 特有方法
    // 每前进一步忠诚度减少 K
    // 忠诚度为 0 时逃跑
    static void setDefaultKloyalty(int K) { K_loyalty = K; }
    void decreaseLoyalty() { loyalty -= K_loyalty; }
    void escape()
    {
        std::cout << "Lion " << m_number << " ran away" << std::endl;
        this->dropWeapon();
        this->setDead();
    }
    Lion(int number, head_color color)
        : Warrior(WarriorType::lion, number, color)
    {
    }
    virtual ~Lion() = default;
};

class Wolf : public Warrior {
public:
    // TODO 特有方法
    // 抢夺敌人武器
    void robWeapon(std::shared_ptr<Warrior> enemy);
    Wolf(int number, head_color color)
        : Warrior(WarriorType::wolf, number, color)
    {
    }
    Wolf() = default;
    Wolf(std::shared_ptr<Warrior> warrior)
    {
        Wolf(warrior->getNumber(), warrior->getHeadColor());
    }
    virtual ~Wolf() = default;
};

#endif // WARRIOR_H