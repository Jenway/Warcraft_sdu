// Headquarter 司令部类
#include "../include/Enums.h"

class Headquarter
{
private:
    head_color m_color;       // 司令部所属阵营
    static int m_defaultLife; // 默认生命元
    int m_life;               // 司令部生命元
    bool m_stop;              // 司令部状态

public:
    inline int life() { return this->m_life; } // 获取司令部生命元

    bool createWarrior(); // 创建战士
    Headquarter(int life, enum head_color color);
    Headquarter();
    ~Headquarter();
};
