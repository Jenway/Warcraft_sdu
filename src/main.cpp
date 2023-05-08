#include <algorithm>
#include <array>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
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
    // part1_test("../test/input.txt");
    return 0;
}

void part3_test(std::string input_file_path)
{
    // FILE* new_stdin;
    // const char* filename = input_file_path.c_str();
    // const char* mode = "r";

    // freopen_s(&new_stdin, filename, mode, stdin);
    // 由文件输入

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
        std::shared_ptr<Headquarter> red_ptr = std::make_shared<Headquarter>(red);
        EventHandler redHandler(red_ptr);

        Headquarter blue(M, head_color::blue);
        std::shared_ptr<Headquarter> blue_ptr = std::make_shared<Headquarter>(blue);
        EventHandler blueHandler(blue_ptr);

        // N => 两个司令部之间一共有N个城市( 1 <= N <= 20 )
        std::vector<std::shared_ptr<City>> cities;
        for (int i = 0; i < N; i++) {
            cities.push_back(std::make_shared<City>(i));
        }

        // K => lion每前进一步，忠诚度就降低K。(0<=K<=100)
        Lion::setDefaultKloyalty(K);

        // TODO  T 的使用 要求输出从0时0分开始，到时间T为止(包括T)的所有事件。T以分钟为单位，0 <= T <= 6000
        // QUESTION: 为什么要用这个？

        // 第二行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的初始生命值。它们都大于0小于等于200
        for (int i = 0; i < 5; i++) {
            int life;
            cin >> life;
            Warrior::setDefaultLife(static_cast<WarriorType>(i), life);
        }

        // 第三行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的攻击力。它们都大于0小于等于200
        for (int i = 0; i < 5; i++) {
            int attack;
            cin >> attack;
            Warrior::setDefaultAttack(static_cast<WarriorType>(i), attack);
        }

        // 输出
        // 对每组数据，先输出一行：

        // Case n:
        // 如对第一组数据就输出 Case 1:
        std::cout << "Case " << i + 1 << ":" << std::endl;
        // 然后按恰当的顺序和格式输出到时间T为止发生的所有事件。每个事件都以事件发生的时间开头，时间格式是“时:分”，“时”有三位，“分”有两位。
        GameClock clock;
        bool redone = true;
        bool blueone = true;
        while (redone || blueone) {
            if (redone) {
                redone = redHandler.onClockUpdate(clock);
            }
            if (blueone) {
                blueone = blueHandler.onClockUpdate(clock);
            }
            clock.update();
        }
    }

    // 样例输入
    // 1
    // 20 1 10 400
    // 20 20 30 10 20
    // 5 5 5 5 5
    // 样例输出
    // Case 1:
    // 000:00 blue lion 1 born
    // Its loyalty is 10
    // 000:10 blue lion 1 marched to city 1 with 10 elements and force 5
    // 000:50 20 elements in red headquarter
    // 000:50 10 elements in blue headquarter
    // 000:55 blue lion 1 has 0 sword 1 bomb 0 arrow and 10 elements
    // 001:05 blue lion 1 ran away
    // 001:50 20 elements in red headquarter
    // 001:50 10 elements in blue headquarter
    // 002:50 20 elements in red headquarter
    // 002:50 10 elements in blue headquarter
    // 003:50 20 elements in red headquarter
    // 003:50 10 elements in blue headquarter
    // 004:50 20 elements in red headquarter
    // 004:50 10 elements in blue headquarter
    // 005:50 20 elements in red headquarter
    // 005:50 10 elements in blue headquarter
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