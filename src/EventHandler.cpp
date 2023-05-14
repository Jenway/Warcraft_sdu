#include "../include/EventHandler.h"
#include "../include/City.h"
#include <iostream>

void EventHandler::setClock(std::shared_ptr<GameClock> clock)
{
    this->clock = clock;
    this->redHQ->setClock(clock);
    this->blueHQ->setClock(clock);
}

bool EventHandler::isGameOver()
{
    // 如果时间结束，游戏结束
    if (clock->isEnd()) {
        return true;
    }
    // 游戏结束的条件是： 1. 双方司令部被占领； 2. 双方司令部的生命元数量都不足以制造武士,且已经没有武士
    if (redHQ->isOccupied() || blueHQ->isOccupied()) {
        return true;
    } else if (redHQ->isStopped() && blueHQ->isStopped()
        && redHQ->getWarriorSum() == 0 && blueHQ->getWarriorSum() == 0) {
        return true;
    } else {
        return false;
    }
}

void EventHandler::onClockUpdate()
{
    if (clock->isEnd()) {
        return;
    }
    switch (clock->getMinutes()) {
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
        battle();

        reportBattle();
        if (true) {
            warriorYell();
        }
        break;
    case 50: // 每小时第 50 分,司令部报告生命值
        reportLife();
        break;
    case 55: // 每小时第 55 分,武士报告武器情况
        reportWeapon();
        break;
    }
}

void EventHandler::spawnWarrior()
{

    this->redHQ->createWarrior();
    this->blueHQ->createWarrior();
}

void EventHandler::lionEscape()
{
    // 从西到东 HQ的容器里存储着所有狮子的指针，所以不用遍历城市
    this->redHQ->lionEscape();
    this->blueHQ->lionEscape();
}

void EventHandler::warriorsMarch()
{

    this->redHQ->warriorsMarch();
    this->blueHQ->warriorsMarch();
}

void EventHandler::wolfSnatch()
{
    this->redHQ->wolfSnatch();
    this->blueHQ->wolfSnatch();
}

void EventHandler::reportBattle()
{
    this->redHQ->reportBattle();
    this->blueHQ->reportBattle();
}

void EventHandler::warriorYell()
{
    this->redHQ->warriorYell();
    this->blueHQ->warriorYell();
}

void EventHandler::reportLife()
{
    this->redHQ->reportLife();
    this->blueHQ->reportLife();
}

void EventHandler::reportWeapon()
{
    this->redHQ->reportWeapon();
    this->blueHQ->reportWeapon();
}

void EventHandler::battle()
{
    // 从西到东遍历城市，塔塔开~
    redHQ->battle();
    for (auto city : cities) {
        city->battle();
    }
    blueHQ->battle();
}

// Path: src\Headquarter.cpp