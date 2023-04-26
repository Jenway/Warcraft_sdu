// src\Headquarter.cpp 司令部类的实现

#include "../include/Headquarter.h"

Headquarter::Headquarter(int life, head_color color)
{
    // 示例输出 000 red headquarter stops making warriors
    this->m_life = life;
    this->m_color = color;
}

Headquarter::~Headquarter()
{
}