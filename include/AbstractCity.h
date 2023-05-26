#if !defined(ABSTRACT_CITY_H)
#define ABSTRACT_CITY_H
#include "Enums.h"
#include <cstddef>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>


class Warrior;
class AbstractCity : public std::enable_shared_from_this<AbstractCity> {
protected:
    // 在这个城市的武士
    std::vector<std::shared_ptr<Warrior>> m_warriors_blue{};
    std::vector<std::shared_ptr<Warrior>> m_warriors_red{};
    // 状态，是否有红蓝武士
    bool m_redWarriorExists = false;
    bool m_blueWarriorExists = false;
    // neighbor
    std::shared_ptr<AbstractCity> m_leftCity{};
    std::shared_ptr<AbstractCity> m_rightCity{};
    // 判断是否是 headquater
    bool isThisHeadquater = false;
    // 战斗了吗
    bool isJustBattled = false;
    // <司令部>是否被敌人占领
    bool isOccupiedByEnemy = false;

public:
    // set neighbor
    void setLeftCity(std::shared_ptr<AbstractCity> city) { m_leftCity = city; }
    void setRightCity(std::shared_ptr<AbstractCity> city) { m_rightCity = city; }
    // 返回下一个城市的shared_ptr
    virtual std::shared_ptr<AbstractCity> nextCity(head_color warrior_color) { return nullptr; }
    virtual std::shared_ptr<AbstractCity> previousCity() { return nullptr; }
    /*返回城市信息*/
    // 返回城市编号
    virtual int getCityNumber() { return 0; }
    // 返回城市颜色
    virtual std::string getHeadColorName() { return ""; }
    // 返回是否是司令部
    bool isHeadquarter() { return this->isThisHeadquater; }
    // 是否有红/蓝武士
    bool getRedWarriorExitst() { return this->m_redWarriorExists; }
    bool getBlueWarriorExitst() { return this->m_blueWarriorExists; }
    WarriorType getRedWarriorType();
    WarriorType getBlueWarriorType();

    // 事件
    void warriorMarch();
    void warriorMarchForColor(std::vector<std::shared_ptr<Warrior>>& warriors);

    // 报告
    void reportWeapon(int hour, int minute);
    void reportWarriorMarchForColor(std::vector<std::shared_ptr<Warrior>>& warriors, int& hour, int& minute);
    void reportWarriorMarch(int hour, int minute);
    void reportBattle(int hour, int minute); // 报告战斗情况

    // battle 相关
    void battle();
    void attackOnBattle(std::shared_ptr<Warrior> red, std::shared_ptr<Warrior> blue);
    void afterBattle();
    bool isOccupied() { return this->isOccupiedByEnemy; }
    void occupy() { this->isOccupiedByEnemy = true; }

    // 事件武士派生类
    void wolfSnatch(int hour, int minute);
    void lionEscape(int hour, int minute);

    // 增删武士
    void addWarrior(std::shared_ptr<Warrior> warrior, head_color color);
    void removeWarrior(head_color color, std::shared_ptr<Warrior> warrior);

    virtual ~AbstractCity() = default;
};
#endif // ABSTRACT_CITY_H