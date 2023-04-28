// Headquarter 司令部类

#if !defined(HEADQUARTER_H)
#define HEADQUARTER_H

#include <memory>
#include <vector>
#include <array>

#include "../include/Enums.h"
#include "../include/Warrior.h"

class Headquarter
{
private:
    static int m_defaultLife; // 默认生命元

    head_color m_color = head_color::red; // 司令部所属阵营
    int m_life = 0;                       // 司令部生命元
    bool m_stop = false;                  // 司令部状态

    std::vector<std::shared_ptr<Warrior>> m_warriors; // 战士列表
    // std::vector<int> m_warriors_count;                // 战士记录
    std::array<int, 5> m_warriors_count = {0, 0, 0, 0, 0};
    int m_totalWarriors = 0; // 战士总数
public:
    int getLife() { return this->m_life; }          // 获取司令部生命元
    head_color getColor() { return this->m_color; } // 获取司令部阵营

    void setLifeViaCost(int cost) { this->m_life -= cost; }

    bool createWarrior();                   // 创建战士
    bool isAbleToCreate(int warrior_index); // 是否能够创建战士

    Headquarter(int life, head_color color);
    Headquarter();
    ~Headquarter() {}
};

#endif // HEADQUARTER_H