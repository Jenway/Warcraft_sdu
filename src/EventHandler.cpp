#include "../include/EventHandler.h"
#include "../include/City.h"

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
        if (isGameOver()) {
            return;
        }
        break;
    case 35: // 每小时第 35 分,wolf 抢武器
        wolfSnatch();
        break;
    case 40: // 每小时第 40 分,报告战斗情况 && 武士欢呼
        battle();
        reportBattle();
        afterBattle();
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
    int hour = clock->getHours();
    int minute = clock->getMinutes();
    this->redHQ->lionEscape(hour, minute);
    for (auto& city : cities) {
        city->lionEscape(hour, minute);
    }
    this->blueHQ->lionEscape(hour, minute);
}

void EventHandler::warriorsMarch()
{
    int hour = clock->getHours();
    int minute = clock->getMinutes();

    this->redHQ->setWarriorArrived();
    this->blueHQ->setWarriorArrived();

    this->redHQ->warriorMarch();
    for (auto& city : cities) {
        city->warriorMarch();
    }
    this->blueHQ->warriorMarch();

    // 从西到东遍历城市，报告 march
    this->redHQ->reportWarriorMarch(hour, minute);
    for (auto& city : cities) {
        city->reportWarriorMarch(hour, minute);
    }
    this->blueHQ->reportWarriorMarch(hour, minute);
}

void EventHandler::wolfSnatch()
{
    int hour = clock->getHours();
    int minute = clock->getMinutes();
    this->redHQ->wolfSnatch(hour, minute);
    for (auto& city : cities) {
        city->wolfSnatch(hour, minute);
    }
    this->blueHQ->wolfSnatch(hour, minute);
}

void EventHandler::reportLife()
{
    this->redHQ->reportLife();
    this->blueHQ->reportLife();
}

void EventHandler::reportWeapon()
{
    int hour = clock->getHours();
    int minute = clock->getMinutes();
    // 从西到东遍历城市，报告武器情况
    for (auto& city : cities) {
        city->reportWeapon(hour, minute);
    }
}

void EventHandler::battle()
{
    // 从西到东遍历城市，塔塔开~
    redHQ->battle();
    for (auto& city : cities) {
        city->battle();
    }
    blueHQ->battle();
}
void EventHandler::reportBattle()
{
    int hour = clock->getHours();
    int minute = clock->getMinutes();
    this->redHQ->reportBattle(hour, minute);
    for (auto& city : cities) {
        city->reportBattle(hour, minute);
    }
    this->blueHQ->reportBattle(hour, minute);
}

void EventHandler::afterBattle()
{
    // 从西到东遍历城市，处理战斗后的事情
    this->redHQ->afterBattle();
    for (auto& city : cities) {
        city->afterBattle();
    }
    this->blueHQ->afterBattle();
}

void EventHandler::setClock(std::shared_ptr<GameClock> clock)
{
    this->clock = clock;
    this->redHQ->setClock(clock);
    this->blueHQ->setClock(clock);
}

void EventHandler::setCities(std::vector<std::shared_ptr<City>> cities)
{
    this->cities = cities;
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

bool EventHandler::isRedWin()
{
    if (blueHQ->isOccupied()) {
        return true;
    } else {
        return false;
    }
}

// Path: src\Headquarter.cpp