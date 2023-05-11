#include "../include/EventHandler.h"

void EventHandler::setClock(std::shared_ptr<GameClock> clock)
{
    this->clock = clock;
    this->redHQ->setClock(clock);
    this->blueHQ->setClock(clock);
}

bool EventHandler::isGameOver()
{
    // 游戏结束的条件是： 1. 双方司令部被占领； 2. 双方司令部的生命元数量都不足以制造武士。
    if (redHQ->isOccupied() || blueHQ->isOccupied()) {
        return true;
    } else if (redHQ->isStopped() && blueHQ->isStopped()) {
        return true;
    } else {
        return false;
    }
}

bool EventHandler::onClockUpdate()
{
    if (clock->isEnd()) {
        return false;
    }
    int hours = clock->getHours();
    int mins = clock->getMinutes();
    switch (mins) {
    case 0: // 每小时第 0 分,武士降生
        spawnWarrior();
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
    // this->redHQ->logEvent(hours);
}

void EventHandler::spawnWarrior()
{

    this->redHQ->createWarrior();

    this->blueHQ->createWarrior();
}

void EventHandler::lionEscape()
{
    this->redHQ->lionEscape();
    this->blueHQ->lionEscape();
}

void EventHandler::warriorsMarch()
{
    this->redHQ->warriorsMarch();
}

void EventHandler::wolfSnatch()
{
    this->redHQ->wolfSnatch();
}

void EventHandler::reportBattle()
{
    this->redHQ->reportBattle();
}

void EventHandler::warriorYell()
{
    this->redHQ->warriorYell();
}

void EventHandler::reportLife()
{
    this->redHQ->reportLife();
}

void EventHandler::reportWeapon(int hour, int minute)
void EventHandler::reportWeapon(int hour, int minute)
{
    this->redHQ->reportWeapon(hour, minute);
}

// Path: src\Headquarter.cpp