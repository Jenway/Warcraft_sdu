# 期末大作业 `魔兽争霸`

## 说明

这是 SDU 计科专业 2022 级 `高级程序语言设计` 课程的大作业，以 old school 游戏魔兽争霸为背景。

经查证原题来自 [北京大学MOOC 程序设计与算法（三）魔兽世界3(2020秋季)](https://http://cxsjsx.openjudge.cn/2018hwall/024/)。

使用 C++ 编写，使用 CMake 进行构建。

代码托管在 [Github](https://github.com/Jenway/Warcraft_sdu)上。

预计在 [Gitee](https://gitee.com/Jenway/Warcraft_sdu) 上 fork 一份。

## 使用

暂定只通过控制台进行输入输出，不使用图形界面。

详细的使用方法请参考 [输入样例](./doc/INTRO.md)

## 编译

需要编译器支持 C++14 标准 (因为使用了 智能指针)

虽然 CMakeLists.txt 要求的最低版本为 3.16，但是切换为更低版本应该也是可以的 (大概)

## 实验报告的 Draft

### 最终完成的任务难度

最终完成的任务难度为 `难度三` ,完成了基本要求和部分附加要求

### 程序文件的组织架构

### [src\main.cpp](./src/main.cpp)

作为程序入口,负责读取输入以初始化数据,并调用 `EventHandler` 处理事件

### [include\EventHandler.h](include\EventHandler.h) && [src\EventHandler.cpp](src\EventHandler.cpp)

`EventHandler` 事件处理类

这个类作为核心类，负责处理所有的事件函数，通过事件函数来调用其他类的函数,实现游戏的运行,调用 `GameClock` 类来控制时间流逝。

- 每小时第 0 分,武士降生
- 每小时第 5 分,lion 逃跑
-每小时第 10 分,武士前进
- 每小时第 35 分,wolf 抢武器
- 每小时第 40 分,报告战斗情况 && 武士欢呼
- 每小时第 50 分,司令部报告生命值
- 每小时第 55 分,武士报告武器情况

### [include\Warrior.h](include\EventHandler.h) && [src\Warrior.cpp](src\EventHandler.cpp)

抽象 `Warrior` ,战士类

包含基本属性如下:

- m_life 生命值
- m_number 战士编号
- m_attack 攻击力
- m_weapon 武器
:

| 战士派生类 | 武器 | 属性 | 技能
| :--------: | :--: | :--: | :--: |
|   `dragon` |  n%3 | 士气 | 战斗结束后,如果还没有战死,就会欢呼 |
|   `ninja`  | n%3, (n+1)%3 | 无 | 使用 bomb 不受伤 |
|  `iceman`  | n%3 | 移动后生命值减少 |无 |
|   `lion`   | 无 | 士气 | 每战斗一次,士气降低 K |
|   `wolf`   | 无 | 无 | 抢夺敌人武器 |

- default_life 每个战士都设置的单独的静态变量，储存其默认生命值

包含方法如下:

- `march` 移动
- `attack` 攻击
- 事件函数以及一些辅助函数

### [include\Weapon.h](include\Weapon.h)

| 武器 | 攻击力 | 耐久度 |
| :--: | :----: | :----: |
| sword | 0.2 * x| 无限 |
| bomb | 0.4 * x | 1 |
| arrow | 0.3 * x| 2|

### [include\AbstractCity.h](include\AbstractCity.h) && [src\AbstractCity.cpp](src\AbstractCity.cpp)

抽象 `AbstractCity` 抽象城市类，派生出 `City` 城市类 和 `Headquarter` 司令部类

包含属性:

- m_warrior_red 存储红方战士
- m_warrior_blue 存储蓝方战士

包含方法:

- 对接 `EventHandler` 的各类子事件函数
- 对接或调用 `Warrior` 在城市间移动与战斗的各类子事件函数以及辅助函数

### [include\Headquarter.h](include\Headquarter.h) && [src\Headquater.cpp](src\Headquater.cpp)

抽象 `Headquarter` 司令部类

包含属性:

- 司令部的颜色
- 制造 `Warrior` 的顺序
- 存储所有的 `Warrior` 指针,防止丢失

包含方法:

- 制造 `Warrior`
- 对接 `EventHandler` 的各类子事件函数

### [include\WeaponFactory.h](include\WeaponFactory.h) && [include\WarriorFactory.h](include\WarriorFactory.h)

抽象 `WeaponFactory` 武器工厂类 和 `WarriorFactory` 战士工厂类,用于生产武器和战士

### [include\City.h](include\City.h)

继承自 `AbstractCity` 类, 抽象 `City` 城市类

- m_city_number 城市编号

### [include\Enum.h](include\Enum.h)

枚举类, 存储各种枚举类型以及部分常量、类型别名等

### [include\GameClock.h](include\GameClock.h) && [src\GameClock.cpp](src\GameClock.cpp)

`GameClock` 游戏时钟类，用于控制时间流逝

### 程序完成的主要逻辑

1. 读取输入,初始化数据,创建 `Headquarter` `City` `EventHandler`  `GameClock` 等对象，然后 两个 `Headquarter` 通过 `WarriorFactory` 制造 `Warrior` ,并将其放入 `City` 中，当制造`Warrior` 时,通过 `WeaponFactory` 制造 `Weapon` 并将其放入 `Warrior` 中

2. 将 `cities` `headquarters` 以及它们内含的 `Warriors`，通过 指针集中在 `EventHandler`中进行调用 , `GameClock` 控制时间流逝
3. 通过 `EventHandler` 处理各类事件
4. 当到达特定时间时,模拟对应事件,通过 `EventHandler` 对接 `AbstractCity` 和 `Headquarter` 的各类子事件函数，从而调用 `Warrior` 的各类子事件函数，完成对应的操作
5. 当满足结束条件时,结束游戏

## 收获与感想

配置 cmake比上次写 (已经鸽掉的) 小恐龙有了些许进步。嘛，可能是因为还没用第三方库的原因。

设计模式，`chatgpt` 告诉我工厂模式这种设计模式，让我不禁感慨自己知识的匮乏，看来，不只需要学习语言特性与轮子，还需要学习设计模式等等。

> warning C4819: 该文件包含不能在当前代码页(936)中表示的字符。请将该文件保存为 Unicode 格式以防止数据丢失

`add_compile_options("$<$[C_COMPILER_ID:MSVC](C_COMPILER_ID:MSVC):/source-charset:utf-8>")`

遇到了循环依赖的问题，解决方法是使用前向声明，但是这样就不能使用 `unique_ptr` 了，因为 `unique_ptr` 需要知道完整的类型信息。

还尝试使用了抽象接口类，这样使得程序更加灵活，但是也带来了一些问题，容易又回到循环依赖的问题。

于是，我就把 `unique_ptr` 换成了 `shared_ptr`。为了实现,多个对象之间共享所有权侧重于生命周期控制,还使用了 `weak_ptr`

------

### 过了很久

离一开始编辑 `README.md` 已经过去了很长时间，现在是 2023年 5 月 18 日，下午 17:18。刚刚做完非图形化界面的部分，没想到花了这么长时间。这次大作业让我学到了很多东西吗？

首先，使用 Cmake 进行构建，这是我第二次使用 Cmake 进行构建，上一次是那个已经鸽掉的小恐龙。似乎并没有学到什么，毕竟 Cmake 有ctest啊,安装啊,打包啊,这些我都没有用到。

花了一段时间来搞编译器，其实这个项目根本就没有什么对编译器的要求，但凡支持 C++ 14 就行，但人菜瘾大，从 g++ 到 用 mingw 链接器的 Clang++,到 MSVC，再到 with MSVC 链接器的 Clang++,怎么说呢，唯一察觉的不同是 `Clang` 会给更丰富的报错警告,`MSVC` 默认在中文环境下会用 GBK，所以还得单独在 CMakeLists 里面加上 UTF-8 的编译选项。

至于老朋友 MinGW ，在网上随便翻资料的时候找到了很好的博文，讲的是 win 平台的 `gcc` 编译器们，从 `MinGW` `TDM-GCC` `MinGW-w64` `WinLibs` 到 `CygWin`和`MSYS2`。讲得很好,又在网上看到一个手动编译 MinGW 的教程，是一个叫`谷雨同学`的人写的，翻了一下 ta 的博客，发现是北大的，在当助教的时候还写了个网站，自己还在写 `C++` 的教程，真是厉害。这个人还做了一个 `VS Code`的 C 编译器配置器，迭代了几个版本，从 C# 到 Rust 的 Tauri。

接下来的日子并不是很顺利，似乎花了很多时间来尝试新的东西，三种智能指针就折腾了一段时间，在用 for_each 循环删除 vector 里的内容的时候还遇上了坑🕳

5 月 7日参加的大英赛，成绩感人, 5 月 12 日的时候,发现这个作业就是完完全全 copy 的 PKU 的某个作业，顿时感觉非常的失望,与 Jeff 聊了聊。

五一的时候去了济南，顺便去了几个 SDU 的校区，千佛山、趵突泉和中心,还去见了 Hai'han 一面，感觉还是很开心的。

15th May ,发现还要赶 英语组队作业的ddl，还有导师会议要准备，第二天体育考试，两周后交离散作业,事情很多..

5 月 3 号，买了份 P5R，很好玩，但是也很耗时间，不过还是很开心的。

至于写这个程序之间种种麻烦糟心事，就不提了。

到底要不要加图形界面呢？

### GUI 界面大致写完了

容我平复平复心情再来完善这个 READEME，先去打包去

### 找出bug所在了

重复调用 paintevnet 是因为子部件 在 painteevent 里更改了`label`的几个属性，导致子部件重绘，结果递归一直调用

至于默认文本，是因为每行前面多了个空格，所以程序就一直卡在那里了，emmm 要不要加一个格式检测呢...
