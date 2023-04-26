#include <iostream>

#include "../include/Headquarter.h"
#include "../include/Warrior.h"

using namespace std;

void union_test();

int main(int argc, char *argv[])
{

    return 0;
}

void union_test()
{
    cout << "Hello World!" << endl;
    Warrior w;
    cout << "Warrior number: " << w.number() << endl;
    Headquarter h;
    cout << "Headquarter life: " << h.life() << endl;
    cout << "done." << endl;

    // 首先，读入测试数据组数，用一个循环来处理每组数据。
    //  对于每组数据，读入司令部的初始生命元和武士的初始生命值。
    //  创建两个司令部对象，分别表示红方和蓝方，传入相应的参数。
    //  输出"Case:n"，n是测试数据的编号。
    //  定义一个变量time，表示当前时间，初始为0。
    //  定义两个布尔变量redStop和blueStop，表示红方和蓝方是否停止制造武士，初始为false。
    //  用一个循环来模拟每个整点发生的事件，直到双方都停止制造武士为止。
    //  在循环中，先调用红方司令部的制造武士的方法，如果返回false，表示不能制造武士，就输出红方停止制造武士的事件，并将redStop设为true。
    //  然后调用蓝方司令部的制造武士的方法，如果返回false，表示不能制造武士，就输出蓝方停止制造武士的事件，并将blueStop设为true。
    //  如果redStop和blueStop都为true，就跳出循环。
    //  否则，将time加一，继续下一轮循环。

    // 第一行是一个整数，代表测试数据组数。
    int test_data_count;
    cin >> test_data_count;
    // 第一行：一个整数M。其含义为，每个司令部一开始都有M个生命元( 1 <= M <= 10000)。
    int M;
    cin >> M;
    // 第二行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的初始生命值。它们都大于0小于等于10000。
    int dragon_life, ninja_life, iceman_life, lion_life, wolf_life;
    cin >> dragon_life >> ninja_life >> iceman_life >> lion_life >> wolf_life;
    Dragon::setLife(dragon_life);
    Ninja::setLife(ninja_life);
    Iceman::setLife(iceman_life);
    Lion::setLife(lion_life);
    Wolf::setLife(wolf_life);

    // fix it later
    head_color h1 = red;
    Headquarter red(M, h1);
    head_color h2 = blue;
    Headquarter blue(M, h2);

    // 时间 
    int time = 0;

    // test_data_count 组测试数据
    for (int i = test_data_count; i >= 0; i--)
    {
        // Case:n
        cout << "Case:" << i << endl;
        while (true)
        {
            
            time++;
        }
    }
}