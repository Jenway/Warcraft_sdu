// Headquarter 司令部类

#if !defined(HEADQUARTER_H)
#define HEADQUARTER_H

#include <array>
#include <memory>
#include <vector>

#include "../include/AbstractCity.h"
#include "../include/Enums.h"
#include "../include/GameClock.h"
#include "../include/Warrior.h"

class Headquarter : public AbstractCity {
private:
    static int m_defaultLife; // 默认生命元

    head_color m_color = head_color::red; // 司令部所属阵营
    int m_life = 0; // 司令部生命元

    // 司令部是否还能制造武士
    bool m_isAbleToCreate = true;
    // 是否被敌人占领
    bool isOccupiedByEnemy = false;
    std::vector<std::shared_ptr<Warrior>> m_warriors; // 战士列表
    // std::vector<int> m_warriors_count;                // 战士记录
    std::array<int, 5> m_warriors_count = { 0, 0, 0, 0, 0 };
    int m_totalWarriors = 0; // 战士总数
    // 在生成战士时，需要按照顺序生成，所以需要一个索引
    int m_warrior_index = 0;

    std::shared_ptr<GameClock> clock;

public:
    // override
    std::shared_ptr<AbstractCity> nextCity(head_color color) override;
    std::shared_ptr<AbstractCity> previousCity() override { return nullptr; }
    // 事件接口
    void logEvent(int hours); // 事件记录
    void lionEscape(); // lion 逃跑
    void warriorsMarch(); // 武士前进
    void wolfSnatch(); // wolf 抢武器
    void reportBattle(); // 报告战斗情况
    void warriorYell(); // 武士欢呼
    void reportLife(); // 司令部报告生命值
    bool isStopped() const { return !this->m_isAbleToCreate; } // 是否停止制造武士
    bool isOccupied() const { return this->isOccupiedByEnemy; } // 是否被敌人占领

    // checkmate~!
    void occupy() { this->isOccupiedByEnemy = true; } // 占领司令部
    void stopCreate() { this->m_isAbleToCreate = false; } // 停止制造武士
    // getter
    int getLife() const { return this->m_life; } // 获取司令部生命元
    head_color getColor() const { return this->m_color; } // 获取司令部阵营
    std::string getColorName() const { return (this->m_color == head_color::red) ? "red" : "blue"; }
    // 获取战士数量
    int getWarriorCount(int warrior_index) const { return this->m_warriors_count[warrior_index]; }
    // 获取战士总数
    int getWarriorSum() const { return this->m_totalWarriors; }
    void setLifeViaCost(int cost) { this->m_life -= cost; }
    void setClock(std::shared_ptr<GameClock> clock) { this->clock = clock; }
    void logWarriorInfo(std::unique_ptr<Warrior>& warrior);
    // setter
    void setWarriorArrived()
    {
        for (auto& warrior : this->m_warriors) {
            warrior->setJustArrived(false);
        }
    }
    bool createWarrior(); // 创建战士
    // 这个函数仅会删除 Headquarter 中的 warrior 指针
    void removeWarriorptrInHead(std::shared_ptr<Warrior> warrior); // 移除战士
    bool isAbleToCreate(int warrior_index); // 是否能够创建战士

    Headquarter(int life, head_color color);
    Headquarter();
    virtual ~Headquarter();
};

#endif // HEADQUARTER_H