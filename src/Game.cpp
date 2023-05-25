#include "../include/Game.h"
#include "../include/AbstractCity.h"
#include "../include/City.h"
#include "../include/Enums.h"
#include "../include/EventHandler.h"
#include "../include/GameClock.h"
#include "../include/GameIO.h"
#include "../include/Headquarter.h"
#include "../include/Warrior.h"
#include "include/Game.h"
#include <memory>
#include <vector>

std::vector<updateData> Game::run()
{

    // 随后，每组样例共三行。

    // 第一行，4个整数 M,N,K,T。

    // M => 每个司令部一开始都有M个生命元( 1 <= M <= 100000)
    Headquarter red(data.M, head_color::red);
    Headquarter blue(data.M, head_color::blue);
    std::shared_ptr<Headquarter> red_ptr = std::make_shared<Headquarter>(red);
    std::shared_ptr<Headquarter> blue_ptr = std::make_shared<Headquarter>(blue);

    EventHandler eventHandler(red_ptr, blue_ptr);
    // N => 两个司令部之间一共有N个城市( 1 <= N <= 20 )
    std::shared_ptr<City> city = std::make_unique<City>(1);
    red_ptr->setRightCity(city);
    city->setLeftCity(red_ptr);
    std::vector<std::shared_ptr<City>> cities;
    this->m_citys = &cities;
    cities.emplace_back(city);

    for (int i = 2; i < data.N; i++) {
        std::shared_ptr<City> cityPtr = std::make_unique<City>(i);
        cities.back()->setRightCity(cityPtr);
        cityPtr->setLeftCity(cities.back());
        cities.emplace_back(cityPtr);
    }
    city = std::make_unique<City>(data.N);
    cities.back()->setRightCity(city);
    city->setLeftCity(cities.back());
    city->setRightCity(blue_ptr);
    blue_ptr->setLeftCity(city);

    cities.emplace_back(city);

    // K => lion每前进一步，忠诚度就降低K。(0<=K<=100)
    Lion::setDefaultKloyalty(data.K);

    // T 的使用 要求输出从0时0分开始，到时间T为止(包括T)的所有事件。T以分钟为单位，0 <= T <= 6000
    std::shared_ptr<GameClock> clock = std::make_shared<GameClock>(data.T);

    // 第二行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的初始生命值。它们都大于0小于等于200
    for (int i = 0; i < 5; i++) {
        Warrior::setDefaultLife(static_cast<WarriorType>(i), data.default_lives[i]);
    }
    // 第三行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的攻击力。它们都大于0小于等于200
    for (int i = 0; i < 5; i++) {
        Warrior::setDefaultAttack(static_cast<WarriorType>(i), data.default_attacks[i]);
    }
    // 输出
    // 对每组数据，先输出一行：

    // Case n:
    // 如对第一组数据就输出 Case 1:
    std::string str = "Case " + std::to_string(data.game_round) + ":\n";
    gameIO::print(str);

    // 然后按恰当的顺序和格式输出到时间T为止发生的所有事件。每个事件都以事件发生的时间开头，时间格式是“时:分”，“时”有三位，“分”有两位。

    eventHandler.setCities(cities);
    eventHandler.setClock(clock);

    bool isGameOver = false;
    std::vector<updateData> update_datas;
    while (!isGameOver) {
        eventHandler.onClockUpdate();
        update_datas.emplace_back(getUpdateData());
        isGameOver = eventHandler.isGameOver();
        clock->update();
    }
    return update_datas;
}

updateData Game::getUpdateData()
{
    updateData update_data;
    update_data.cityNumber = this->data.N;

    for (auto& city : *m_citys) {
        if (city->getRedWarriorExitst()) {
            update_data.redWarrior.push_back(city->getRedWarriorType());
        }
        if (city->getBlueWarriorExitst()) {
            update_data.blueWarrior.push_back(city->getBlueWarriorType());
        }
    }
    return update_data;
}