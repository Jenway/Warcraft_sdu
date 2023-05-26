// this is the commandline version of the program

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "include/City.h"
#include "include/Enums.h"
#include "include/EventHandler.h"
#include "include/GameIO.h"
#include "include/Headquarter.h"

using std::cin;

void part3_test();
int main()
{
    part3_test();
}

void part3_test()
{
    // 判断 output.txt 是否存在，如果存在，清空
    std::ofstream ofs("output.txt", std::ios::trunc);
    ofs.close();

    // 第一行是t,代表测试数据组数
    int test_data_count;
    cin >> test_data_count;

    // 随后，每组样例共三行。
    for (int i = 0; i < test_data_count; i++) {
        // 第一行，4个整数 M,N,K,T。
        int M, N, K, T;
        cin >> M >> N >> K >> T;

        // M => 每个司令部一开始都有M个生命元( 1 <= M <= 100000)
        Headquarter red(M, head_color::red);
        Headquarter blue(M, head_color::blue);
        std::shared_ptr<Headquarter> red_ptr = std::make_shared<Headquarter>(red);
        std::shared_ptr<Headquarter> blue_ptr = std::make_shared<Headquarter>(blue);

        EventHandler eventHandler(red_ptr, blue_ptr);

        // N => 两个司令部之间一共有N个城市( 1 <= N <= 20 )
        std::shared_ptr<City> city = std::make_unique<City>(1);
        red_ptr->setRightCity(city);
        city->setLeftCity(red_ptr);
        std::vector<std::shared_ptr<City>> cities;
        cities.emplace_back(city);

        for (int i = 2; i < N; i++) {
            std::shared_ptr<City> cityPtr = std::make_unique<City>(i);
            cities.back()->setRightCity(cityPtr);
            cityPtr->setLeftCity(cities.back());
            cities.emplace_back(cityPtr);
        }
        city = std::make_unique<City>(N);
        cities.back()->setRightCity(city);
        city->setLeftCity(cities.back());
        city->setRightCity(blue_ptr);
        blue_ptr->setLeftCity(city);

        cities.emplace_back(city);

        // K => lion每前进一步，忠诚度就降低K。(0<=K<=100)
        Lion::setDefaultKloyalty(K);

        // T 的使用 要求输出从0时0分开始，到时间T为止(包括T)的所有事件。T以分钟为单位，0 <= T <= 6000
        std::shared_ptr<GameClock> clock = std::make_shared<GameClock>(T);

        // 第二行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的初始生命值。它们都大于0小于等于200

        // istream_iterator<int> i1(cin), i2;
        // vector<int> lives { i1, i2 };
        for (int i = 0; i < 5; i++) {
            int life;
            cin >> life;
            Warrior::setDefaultLife(static_cast<WarriorType>(i), life);
        }
        // 第三行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的攻击力。它们都大于0小于等于200
        // istream_iterator<int> i3(cin), i4;
        // vector<int> attacks { i3, i4 };
        for (int i = 0; i < 5; i++) {
            int attack;
            cin >> attack;
            Warrior::setDefaultAttack(static_cast<WarriorType>(i), attack);
        }

        // 输出
        // 对每组数据，先输出一行：

        // Case n:
        // 如对第一组数据就输出 Case 1:
        std::stringstream ss;
        ss << "Case " << i + 1 << ":" << std::endl;
        gameIO::print(ss.str());
        // 然后按恰当的顺序和格式输出到时间T为止发生的所有事件。每个事件都以事件发生的时间开头，时间格式是“时:分”，“时”有三位，“分”有两位。

        eventHandler.setCities(cities);
        eventHandler.setClock(clock);

        bool isGameOver = false;
        while (!isGameOver) {
            eventHandler.onClockUpdate();
            isGameOver = eventHandler.isGameOver();
            clock->update();
        }
    }
}