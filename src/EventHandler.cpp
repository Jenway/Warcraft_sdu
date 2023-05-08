#include "../include/EventHandler.h"

bool EventHandler::onClockUpdate(GameClock& clock)
{

    int hours = clock.getHours();
    int mins = clock.getMinutes();
    switch (mins) {
    case 0: // 每小时第 0 分,武士降生
        spawnWarrior();
        logEvent(hours);
        break;
    case 5: // 每小时第 5 分,lion 逃跑
        lionEscape();
        break;
    case 10: // 每小时第 10 分,武士前进
        warriorsMarch();
        break;
    case 35: // 每小时第 35 分,wolf 抢武器
        wolfSnatch();
        break;
    case 40: // 每小时第 40 分,报告战斗情况 && 武士欢呼
        reportBattle();
        if (true) {
            warriorYell();
        }
        break;
    case 50: // 每小时第 50 分,司令部报告生命值
        reportLife();
        break;
    case 55: // 每小时第 55 分,武士报告武器情况
        reportWeapon(hours, mins);
        break;
    }
    return true;
}

void EventHandler::logEvent(int hours)
{
    // this->HQ->logEvent(hours);
}

void EventHandler::spawnWarrior()
{
    this->HQ->createWarrior();
}

void EventHandler::lionEscape()
{
    this->HQ->lionEscape();
}

void EventHandler::warriorsMarch()
{
    this->HQ->warriorsMarch();
}

void EventHandler::wolfSnatch()
{
    this->HQ->wolfSnatch();
}

void EventHandler::reportBattle()
{
    this->HQ->reportBattle();
}

void EventHandler::warriorYell()
{
    this->HQ->warriorYell();
}

void EventHandler::reportLife()
{
    this->HQ->reportLife();
}

void EventHandler::reportWeapon(int hour, int minute)
{
    this->HQ->reportWeapon(hour, minute);
}

// Path: src\Headquarter.cpp