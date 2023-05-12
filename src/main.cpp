#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <memory>
#include <ranges>
#include <string>
#include <vector>

#include <stdio.h>

#include "../include/City.h"
#include "../include/Enums.h"
#include "../include/EventHandler.h"
#include "../include/GameClock.h"
#include "../include/Headquarter.h"
#include "../include/Warrior.h"
using namespace std;

void part1_test(std::string input_file_path);
void part3_test(std::string input_file_path);

int main(int argc, char* argv[])
{
    // part1_test();
    // return 0;
}

void part3_test(std::string input_file_path)
{

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
        std::vector<std::shared_ptr<City>> cities;
        for (int i = 0; i < N; i++) {
            cities.push_back(std::make_shared<City>(i));
        }

        // K => lion每前进一步，忠诚度就降低K。(0<=K<=100)
        Lion::setDefaultKloyalty(K);

        // T 的使用 要求输出从0时0分开始，到时间T为止(包括T)的所有事件。T以分钟为单位，0 <= T <= 6000
        GameClock::setEndTime(T);

        // 第二行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的初始生命值。它们都大于0小于等于200

        istream_iterator<int> i1(cin), i2;
        vector<int> lives { i1, i2 };
        for (int i = 0; i < 5; i++) {
            Warrior::setDefaultLife(static_cast<WarriorType>(i), lives[i]);
        }

        // 第三行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的攻击力。它们都大于0小于等于200
        istream_iterator<int> i3(cin), i4;
        vector<int> attacks { i3, i4 };
        for (int i = 0; i < 5; i++) {
            Warrior::setDefaultAttack(static_cast<WarriorType>(i), attacks[i]);
        }

        // 输出
        // 对每组数据，先输出一行：

        // Case n:
        // 如对第一组数据就输出 Case 1:
        std::cout << "Case " << i + 1 << ":" << std::endl;
        // 然后按恰当的顺序和格式输出到时间T为止发生的所有事件。每个事件都以事件发生的时间开头，时间格式是“时:分”，“时”有三位，“分”有两位。
        std::shared_ptr<GameClock> clock = std::make_shared<GameClock>();
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

void part1_test(std::string input_file_path)
{
    // 由文件输入
    // FILE* new_stdin;
    // const char* filename = input_file_path.c_str();
    // const char* mode = "r";
    // freopen_s(&new_stdin, filename, mode, stdin);

    // 第一行是一个整数，代表测试数据组数。
    int test_data_count;
    cin >> test_data_count;
    // 第一行：一个整数M。其含义为，每个司令部一开始都有M个生命元( 1 <= M <= 10000)。
    int M;
    cin >> M;
    // 第二行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的初始生命值。它们都大于0小于等于10000。
    for (int i = 0; i < 5; i++) {
        int life;
        cin >> life;
        Warrior::setDefaultLife(static_cast<WarriorType>(i), life);
    }

    Headquarter red(M, head_color::red);
    Headquarter blue(M, head_color::blue);

    // test_data_count 组测试数据
    for (int i = test_data_count; i > 0; i--) {
        // Case:n
        cout << "Case:" << i << endl;

        bool redone = true;
        bool blueone = true;
        while (redone || blueone) {
            if (redone) {
                redone = red.createWarrior();
            }
            if (blueone) {
                blueone = blue.createWarrior();
            }
        }
    }
}