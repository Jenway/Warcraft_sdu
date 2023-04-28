#include <iostream>

#include "../include/Headquarter.h"
#include "../include/Warrior.h"

using namespace std;

void part1_test();

int main(int argc, char *argv[])
{
    part1_test();
    return 0;
}

void part1_test()
{

    // 第一行是一个整数，代表测试数据组数。
    int test_data_count;
    cin >> test_data_count;
    // 第一行：一个整数M。其含义为，每个司令部一开始都有M个生命元( 1 <= M <= 10000)。
    int M;
    cin >> M;
    // 第二行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的初始生命值。它们都大于0小于等于10000。
    for (int i = 0; i < 5; i++)
    {
        int life;
        cin >> life;
        Warrior::setDefaultLife(static_cast<WarriorType>(i), life);
    }

    Headquarter red(M, head_color::red);
    Headquarter blue(M, head_color::blue);

    // test_data_count 组测试数据
    for (int i = test_data_count; i > 0; i--)
    {
        // Case:n
        cout << "Case:" << i << endl;

        bool redone = true;
        bool blueone = true;
        while (redone || blueone)
        {
            if (redone)
            {
                redone = red.createWarrior();
            }
            if (blueone)
            {
                blueone = blue.createWarrior();
            }
        }
    }
}